#include "../../../Header Files/Components/RootManager/RootManager.h"

RootManager::RootManager()
{
	dataAccessLayer = new DAL();
	messagesQueue = new MessagesQueue();
	smtpLayer = new SmtpLayer();
	sessionsListener = new SessionListener();
	clientSessionsMutex = CreateMutex(NULL, FALSE, NULL);
}


RootManager::~RootManager()
{
	delete dataAccessLayer;
	delete messagesQueue;
	delete smtpLayer;
	delete sessionsListener;
	CloseHandle(clientSessionsMutex);
}

void RootManager::Start()
{
	smtpLayer->Initialize(*messagesQueue);
	sessionsListener->Initialize(*this);
}


void RootManager::CreateClientAsync(int socketfd)
{
	DWORD dwThreadId;
	ClientSessionObjects* sessionObjects = new ClientSessionObjects();
	CreateClientParamsPointer params = new CreateClientParams(*sessionObjects, *this, socketfd);
	sessionObjects->thread = CreateThread(NULL, 0, CreateClient, params, 0, &dwThreadId);
}

DWORD WINAPI RootManager::CreateClient(LPVOID lpParam)
{
	CreateClientParamsPointer params = (CreateClientParamsPointer)lpParam;
	ClientSessionObjects& sessionObjects = params->objectsToUpdate;
	RootManager& rootManager = params->rootManager;

	sessionObjects.clientSession = new ClientSession();
	sessionObjects.cipher = new Cipher();
	sessionObjects.tcpLayer = new TcpLayer();

	WaitForSingleObject(rootManager.clientSessionsMutex, INFINITE);
	rootManager.clientSessions.push_back(&sessionObjects);
	SessionState initialState = rootManager.clientSessions.size() < 1000 ? SessionState::Unauthorized : SessionState::Busy;
	ReleaseMutex(rootManager.clientSessionsMutex);

	sessionObjects.clientSession->Initialize(*sessionObjects.cipher, *rootManager.messagesQueue, initialState, *rootManager.dataAccessLayer, rootManager);
	sessionObjects.cipher->Initialize(*sessionObjects.tcpLayer);
	sessionObjects.tcpLayer->Initialize(params->socketFd);

	sessionObjects.clientSession->StartAsync();
}


void RootManager::RegisterClientEnded(IClientSessionManager &clientSessionManager)
{
	WaitForSingleObject(clientSessionsMutex, INFINITE);
	for (int i = 0; i < clientSessions.size(); ++i)
	{
		if (&clientSessionManager == clientSessions[i]->clientSession)
		{
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
	for (int i = 0; i < rootManager.clientSessions.size(); ++i)
	{
		if (threadHandle == rootManager.clientSessions[i]->thread)
		{
			delete rootManager.clientSessions[i]->cipher;
			delete rootManager.clientSessions[i]->clientSession;
			delete rootManager.clientSessions[i]->tcpLayer;
			rootManager.clientSessions.erase(rootManager.clientSessions.begin() + i);
		}
	}
	ReleaseMutex(rootManager.clientSessionsMutex);

	delete params;
}