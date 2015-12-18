#include "../../../Header Files/Components/RootManager/RootManager.h"

RootManager::RootManager()
{
	dataAccessLayer = new DAL();
	messagesQueue = new MessagesQueue();
	smtpLayer = new SmtpLayer();
	sessionsListener = new SessionListener();
	clentSessionsMutex = CreateMutex(NULL, FALSE, NULL);
}


RootManager::~RootManager()
{
}

void RootManager::Start()
{
	smtpLayer->Initialize(*messagesQueue);
	sessionsListener->Initialize(*this);
}


void RootManager::CreateClientAsync(int socketfd)
{
	ClientSessionTrio* sessionTrio = new ClientSessionTrio();
	sessionTrio->clientSession = new ClientSession();
	sessionTrio->cipher = new Cipher();
	sessionTrio->tcpLayer = new TcpLayer();

	WaitForSingleObject(clentSessionsMutex, INFINITE);
	clientSessions.push_back(sessionTrio);
	ReleaseMutex(clentSessionsMutex);

	SessionState initialState = clientSessions.size() < 1000 ? SessionState::Unauthorized : SessionState::Busy;
	sessionTrio->clientSession->Initialize(*sessionTrio->cipher, *messagesQueue, initialState, *dataAccessLayer, *this);
	sessionTrio->cipher->Initialize(*sessionTrio->tcpLayer);
	sessionTrio->tcpLayer->Initialize(socketfd);

	sessionTrio->clientSession->StartAsync();
}


void RootManager::RegisterClientEnded(IClientSessionManager &clientSessionManager, unsigned int clientThreadId)
{
	WaitForSingleObject(clentSessionsMutex, INFINITE);
	for (int i = 0; i < clientSessions.size(); ++i)
	{
		if (&clientSessionManager == clientSessions[i]->clientSession)
		{
			DWORD dwThreadId;
			WaitForClientThreadToEndAsnycParamsPointer threadParams 
				= new WaitForClientThreadToEndAsnycParams(clientSessionManager, *this, clientThreadId);
			CreateThread(
				NULL,
				0,
				WaitForClientThreadToEndAsnyc,
				threadParams,
				0,
				&dwThreadId);
			break;
		}
	}
	ReleaseMutex(clentSessionsMutex);
}

DWORD WINAPI RootManager::WaitForClientThreadToEndAsnyc(LPVOID lpParam)
{
	WaitForClientThreadToEndAsnycParamsPointer params = (WaitForClientThreadToEndAsnycParamsPointer)lpParam;
	throw "Not implemnetd";

}