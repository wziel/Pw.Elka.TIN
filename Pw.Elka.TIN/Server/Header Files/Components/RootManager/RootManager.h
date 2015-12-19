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
	///class that stores objects per client session
	class ClientSessionObjects
	{
	public:
		ClientSession* clientSession;
		Cipher* cipher;
		TcpLayer* tcpLayer;
		HANDLE thread;
	};

	///components of whole system
	std::vector<ClientSessionObjects*> clientSessions;
	MessagesQueue* messagesQueue;
	SessionListener* sessionsListener;
	SmtpLayer* smtpLayer;
	DAL* dataAccessLayer;

	///mutex for accessing clientsessions - since they are accessed from multiple threads
	HANDLE clientSessionsMutex;

	///thread function that waits for a specified client session thread to end and then notifies rootManger of that event
	static DWORD WINAPI WaitForClientThreadToEnd(LPVOID lpParam);
	///parameters for the above thread
	typedef struct WaitForClientThreadToEndParams
	{
		HANDLE thread;
		RootManager &rootManager;
		WaitForClientThreadToEndParams(HANDLE thread, RootManager& rootMng) : thread(thread), rootManager(rootMng) { }
	} *WaitForClientThreadToEndParamsPointer;

	///thread function that creates client objects
	static DWORD WINAPI CreateClient(LPVOID lpParam);
	///parameters for the above thread
	typedef struct CreateClientParams
	{
		ClientSessionObjects& objectsToUpdate;
		RootManager &rootManager;
		int socketFd;
		CreateClientParams(ClientSessionObjects& sessionObjects, RootManager& rootMng, int socketFd) 
			: objectsToUpdate(sessionObjects), rootManager(rootMng), socketFd(socketFd) { }
	} *CreateClientParamsPointer;

public:
	RootManager();
	~RootManager();

	///function that should be used to start the whole system
	void Start();

	///IClientCreator interface
	void CreateClientAsync(int socketfd) override;

	///IClientManager interface
	void RegisterClientEnded(IClientSessionManager &clientSessionManager) override;
};

