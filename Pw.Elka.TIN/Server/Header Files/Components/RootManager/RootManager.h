#pragma once

#include "../../Interfaces/IClientCreator.h"
#include "../../Interfaces/IClientManager.h"
#include "../ClientSession/ClientSession.h"
#include "../Cipher/Cipher.h"
#include "../TcpLayer/TcpLayer.h"
#include "../SessionListener/SessionListener.h"
#include "../SmtpLayer/SmtpLayer.h"
#include "../DAL/DAL.h"
#include "../../Shared/MessagesQueue.h"
#include "../../Shared/SessionState.h"

#include<Windows.h>

class RootManager :
	public IClientCreator, public IClientManager
{
private:
	class ClientSessionTrio
	{
	public:
		ClientSession* clientSession;
		Cipher* cipher;
		TcpLayer* tcpLayer;
	};
	std::vector<ClientSessionTrio*> clientSessions;
	HANDLE clentSessionsMutex;

	MessagesQueue* messagesQueue;
	SessionListener* sessionsListener;
	SmtpLayer* smtpLayer;
	DAL* dataAccessLayer;

	typedef struct WaitForClientThreadToEndAsnycParams
	{
		IClientSessionManager &clientSessionManager;
		RootManager &rootManager;
		DWORD WINAPI clientThreadId;
		WaitForClientThreadToEndAsnycParams(IClientSessionManager& clientMng, RootManager& rootMng, DWORD WINAPI threadId)
			: clientSessionManager(clientMng), rootManager(rootMng)
		{
			clientThreadId = threadId;
		}
	} *WaitForClientThreadToEndAsnycParamsPointer;
	static DWORD WINAPI WaitForClientThreadToEndAsnyc(LPVOID lpParam);

public:
	RootManager();
	~RootManager();

	void Start();
	void CreateClientAsync(int socketfd) override;
	void RegisterClientEnded(IClientSessionManager &clientSessionManager, unsigned int clientThreadId) override;
	void DeleteClientObjects(IClientSessionManager& manager);
};

