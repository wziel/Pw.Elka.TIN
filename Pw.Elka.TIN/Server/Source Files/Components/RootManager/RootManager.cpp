#include "../../../Header Files/Components/RootManager/RootManager.h"

RootManager::RootManager()
{
	dataAccessLayer = new DAL();
	messagesQueue = new MessagesQueue();
	smtpLayer = new SmtpLayer(messagesQueue);
	sessionsListener = new SessionListener(*this);
	adminView = new AdministratorView(*this, *dataAccessLayer);
	clientSessionsMutex = CreateMutex(NULL, FALSE, NULL);
}


RootManager::~RootManager()
{
	delete dataAccessLayer;
	delete messagesQueue;
	delete smtpLayer;
	delete sessionsListener;
	while (clientSessions.size() > 0)
	{
		ClientSessionObjects* clientSession = clientSessions[clientSessions.size() - 1];
		delete clientSession->cipher;
		delete clientSession->clientSession;
		delete clientSession->tcpLayer;
		delete clientSession;
		clientSessions.pop_back();
	}
	CloseHandle(clientSessionsMutex);
}

void RootManager::Start()
{
	DWORD dwThreadId;
	smtpLayerThreadHandle = CreateThread(NULL, 0, StartSmtpLayer, smtpLayer, 0, &dwThreadId);
	sessionsListenerThreadHandle = CreateThread(NULL, 0, StartSessionsListener, sessionsListener, 0, &dwThreadId);

	adminView->Start();
}

void RootManager::End()
{
	isClosingDown = true;
	sessionsListener->End();
	messagesQueue->End();

	WaitForSingleObject(clientSessionsMutex, INFINITE);
	for (int i = clientSessions.size() - 1; i >= 0; --i)
	{
		clientSessions[i]->tcpLayer->End();
	}
	ReleaseMutex(clientSessionsMutex);

	WaitForSingleObject(smtpLayerThreadHandle, INFINITE);
	WaitForSingleObject(sessionsListenerThreadHandle, INFINITE);
	WaitForSingleObject(clientSessionsMutex, INFINITE);
	for (int i = clientSessions.size() - 1; i >= 0; --i)
	{
		WaitForSingleObject(clientSessions[i]->thread, INFINITE);
	}
	ReleaseMutex(clientSessionsMutex);
}

DWORD WINAPI RootManager::StartSmtpLayer(LPVOID lpParam)
{
	SmtpLayer* smtpLayer = (SmtpLayer*)lpParam;
	smtpLayer->Start();
	return 0;
}

DWORD WINAPI RootManager::StartSessionsListener(LPVOID lpParam)
{
	SessionListener* sessionsLister = (SessionListener*)lpParam;
	sessionsLister->Start();
	return 0;
}

void RootManager::CreateClientAsync(int socketfd, struct sockaddr_in newClientAddressStruct, int newClientAddressLenght)
{
	DWORD dwThreadId;
	ClientSessionObjects* sessionObjects = new ClientSessionObjects();
	CreateClientParamsPointer params = new CreateClientParams(*sessionObjects, *this, socketfd);
	sessionObjects->thread = CreateThread(NULL, 0, CreateClient, params, 0, &dwThreadId);
	sessionObjects->state = ClientSessionState::Starting;

	WaitForSingleObject(clientSessionsMutex, INFINITE);
	if (!isClosingDown)
	{
		clientSessions.push_back(sessionObjects);
	}
	ReleaseMutex(clientSessionsMutex);
}

DWORD WINAPI RootManager::CreateClient(LPVOID lpParam)
{
	CreateClientParamsPointer params = (CreateClientParamsPointer)lpParam;
	ClientSessionObjects& sessionObjects = params->objectsToUpdate;
	RootManager& rootManager = params->rootManager;

	SessionState initialState = rootManager.clientSessions.size() < 1000 ? SessionState::Unauthorized : SessionState::Busy;

	sessionObjects.tcpLayer = new TcpLayer(params->socketFd);
	sessionObjects.cipher = new Cipher(*sessionObjects.tcpLayer);
	sessionObjects.clientSession = new ClientSession(*sessionObjects.cipher, *rootManager.messagesQueue, initialState, *rootManager.dataAccessLayer, rootManager);
	sessionObjects.connectionId = rootManager.connectionIdHighWaterMark++;

	sessionObjects.clientSession->Start();
	sessionObjects.state = ClientSessionState::Working;
	return 0;
}


void RootManager::RegisterClientEnded(IClientSessionManager &clientSessionManager)
{
	WaitForSingleObject(clientSessionsMutex, INFINITE);
	for (unsigned int i = 0; i < clientSessions.size(); ++i)
	{
		if (&clientSessionManager == clientSessions[i]->clientSession)
		{
			clientSessions[i]->state = ClientSessionState::Ending;
			DWORD dwThreadId;
			WaitForClientThreadToEndParamsPointer threadParams
				= new WaitForClientThreadToEndParams(clientSessions[i]->thread, *this);
			CreateThread(NULL, 0, WaitForClientThreadToEnd, threadParams, 0, &dwThreadId);
			break;
		}
	}
	ReleaseMutex(clientSessionsMutex);
}

DWORD WINAPI RootManager::WaitForClientThreadToEnd(LPVOID lpParam)
{
	WaitForClientThreadToEndParamsPointer params = (WaitForClientThreadToEndParamsPointer)lpParam;
	RootManager& rootManager = params->rootManager;
	HANDLE threadHandle = params->thread;
	WaitForSingleObject(params->thread, INFINITE);

	int id;

	WaitForSingleObject(rootManager.clientSessionsMutex, INFINITE);
	for (unsigned int i = 0; i < rootManager.clientSessions.size(); ++i)
	{
		if (threadHandle == rootManager.clientSessions[i]->thread)
		{
			id = rootManager.clientSessions[i]->connectionId;

			delete rootManager.clientSessions[i]->cipher;
			delete rootManager.clientSessions[i]->clientSession;
			delete rootManager.clientSessions[i]->tcpLayer;
			delete rootManager.clientSessions[i];
			rootManager.clientSessions.erase(rootManager.clientSessions.begin() + i);
		}
	}
	ReleaseMutex(rootManager.clientSessionsMutex);
	std::cout << "Session " << id << " ended successfully\n";
	delete params;
	return 0;
}


std::vector<ClientSessionView> RootManager::GetAllClientSessionViews()
{
	std::vector<ClientSessionView> views;

	WaitForSingleObject(clientSessionsMutex, INFINITE);
	for (unsigned int i = 0; i < clientSessions.size(); ++i)
	{
		ClientSessionView view;
		view.clientName = clientSessions[i]->clientSession->GetClientName();
		view.connectionId = clientSessions[i]->connectionId;
		view.state = clientSessions[i]->state;

		views.push_back(view);
	}
	ReleaseMutex(clientSessionsMutex);

	return views;
}

void RootManager::EndClientSession(unsigned clientSessionViewId)
{
	WaitForSingleObject(clientSessionsMutex, INFINITE);
	for (unsigned int i = 0; i < clientSessions.size(); ++i)
	{
		if (clientSessions[i]->connectionId == clientSessionViewId)
		{
			if (clientSessions[i]->state == ClientSessionState::Ending)
			{
				throw "Not implemented";
			}

			clientSessions[i]->tcpLayer->End();
			clientSessions[i]->state = ClientSessionState::Ending;
			DWORD dwThreadId;
			WaitForClientThreadToEndParamsPointer threadParams
				= new WaitForClientThreadToEndParams(clientSessions[i]->thread, *this);
			CreateThread(NULL, 0, WaitForClientThreadToEnd, threadParams, 0, &dwThreadId);
			break;
		}
	}
	ReleaseMutex(clientSessionsMutex);
}