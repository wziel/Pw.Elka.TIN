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

RootManager::ClientSessionObjects::~ClientSessionObjects()
{
	delete clientSession;
	delete cipher;
	delete tcpLayer;
	delete rawTcpLayer;
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
	sessionsListener->End();
	messagesQueue->End();

	WaitForSingleObject(clientSessionsMutex, INFINITE);
	isClosingDown = true;
	for (int i = clientSessions.size() - 1; i >= 0; --i)
	{
		clientSessions[i]->rawTcpLayer->End();
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
	delete lpParam;
	return 0;
}

DWORD WINAPI RootManager::StartSessionsListener(LPVOID lpParam)
{
	SessionListener* sessionsLister = (SessionListener*)lpParam;
	sessionsLister->Start();
	delete lpParam;
	return 0;
}

void RootManager::CreateClientAsync(int socketfd, struct sockaddr_in newClientAddressStruct, int newClientAddressLenght)
{
	DWORD dwThreadId;

	WaitForSingleObject(clientSessionsMutex, INFINITE);
	if (!isClosingDown)
	{
		ClientSessionObjects* sessionObjects = new ClientSessionObjects();

		SessionState initialState = clientSessions.size() < Configuration::getConfiguration().getMaxSession()
			? SessionState::Unauthorized : SessionState::Busy;
		sessionObjects->rawTcpLayer = new RawTcpLayer(socketfd);
		sessionObjects->tcpLayer = new TcpLayer(*sessionObjects->rawTcpLayer);
		sessionObjects->cipher = new Cipher(*sessionObjects->tcpLayer);
		sessionObjects->clientSession = new ClientSession(*sessionObjects->cipher, *messagesQueue, initialState, *dataAccessLayer, *this);
		sessionObjects->connectionId = connectionIdHighWaterMark++;

		CreateClientParamsPointer params = new CreateClientParams(*sessionObjects);
		sessionObjects->thread = CreateThread(NULL, 0, CreateClient, params, 0, &dwThreadId);
		sessionObjects->state = ClientSessionState::Starting;
		clientSessions.push_back(sessionObjects);
	}
	ReleaseMutex(clientSessionsMutex);
}

DWORD WINAPI RootManager::CreateClient(LPVOID lpParam)
{
	CreateClientParamsPointer params = (CreateClientParamsPointer)lpParam;
	ClientSessionObjects& sessionObjects = params->objectsToUpdate;

	sessionObjects.clientSession->Start();
	delete lpParam;
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

	WaitForSingleObject(rootManager.clientSessionsMutex, INFINITE);
	for (unsigned int i = 0; i < rootManager.clientSessions.size(); ++i)
	{
		if (threadHandle == rootManager.clientSessions[i]->thread)
		{
			delete rootManager.clientSessions[i];
			rootManager.clientSessions.erase(rootManager.clientSessions.begin() + i);
		}
	}
	ReleaseMutex(rootManager.clientSessionsMutex);
	delete lpParam;
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

bool RootManager::DoesSessionExistForClient(string loginname)
{
	bool toReturn = false;

	WaitForSingleObject(clientSessionsMutex, INFINITE);
	for (unsigned int i = 0; i < clientSessions.size(); ++i)
	{
		if (clientSessions[i]->clientSession->GetClientName() == loginname)
		{
			toReturn = true;
			break;
		}
	}
	ReleaseMutex(clientSessionsMutex);

	return toReturn;
}

bool RootManager::EndClientSession(unsigned clientSessionViewId)
{
	bool clientFound = false;

	WaitForSingleObject(clientSessionsMutex, INFINITE);
	for (unsigned int i = 0; i < clientSessions.size(); ++i)
	{
		if (clientSessions[i]->connectionId == clientSessionViewId)
		{
			if (clientSessions[i]->state == ClientSessionState::Ending)
			{
				throw "Not implemented";
			}

			clientSessions[i]->rawTcpLayer->End();
			clientSessions[i]->state = ClientSessionState::Ending;
			DWORD dwThreadId;
			WaitForClientThreadToEndParamsPointer threadParams
				= new WaitForClientThreadToEndParams(clientSessions[i]->thread, *this);
			CreateThread(NULL, 0, WaitForClientThreadToEnd, threadParams, 0, &dwThreadId);

			clientFound = true;
			break;
		}
	}
	ReleaseMutex(clientSessionsMutex);

	return clientFound;
}