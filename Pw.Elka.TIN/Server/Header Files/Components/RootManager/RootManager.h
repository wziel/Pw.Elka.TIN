#pragma once

#include "../../Interfaces/IClientCreator.h"
#include "../../Interfaces/IClientManager.h"
#include "../../Interfaces/IClientSessionsRegister.h"
#include "../ClientSession/ClientSession.h"
#include "../Cipher/Cipher.h"
#include "../TcpLayer/TcpLayer.h"
#include "../SessionListener/SessionListener.h"
#include "../DAL/DAL.h"
#include "../../Shared/MessagesQueue.h"
#include "../SmtpLayer/SmtpLayer.h"
#include "../../Shared/SessionState.h"
#include "Enums.h"
#include "../AdministratorView/ClientSessionView.h"
#include "../AdministratorView/AdministratorView.h"

#define _WINSOCKAPI_ 
#include<Windows.h>

class RootManager :
	public IClientCreator, public IClientManager, public IClientSessionsRegister
{
private:

	///class that stores objects per client session
	class ClientSessionObjects
	{
	public:
		unsigned connectionId;
		ClientSession* clientSession;
		Cipher* cipher;
		TcpLayer* tcpLayer;
		HANDLE thread;
		ClientSessionState state;
	};

	///the biggest number of client id assigned
	unsigned connectionIdHighWaterMark = 0;

	///mutex for accessing clientsessions - since they are accessed from multiple threads
	HANDLE clientSessionsMutex;

	///components of whole system
	std::vector<ClientSessionObjects*> clientSessions;
	MessagesQueue* messagesQueue;
	DAL* dataAccessLayer;
	SessionListener* sessionsListener;
	SmtpLayer* smtpLayer;
	AdministratorView* adminView;

	HANDLE sessionsListenerThreadHandle;
	HANDLE smtpLayerThreadHandle;

	///thread functions to start application-wide components that have own threads.
	static DWORD WINAPI StartSmtpLayer(LPVOID lpParam);
	static DWORD WINAPI StartSessionsListener(LPVOID lpParam);

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
		CreateClientParams(ClientSessionObjects& sessionObjects) : objectsToUpdate(sessionObjects) { }
	} *CreateClientParamsPointer;

	bool isClosingDown = false;

public:
	RootManager();
	~RootManager();

	///function that should be used to start the whole system
	void Start();
	void End();

	///IClientCreator interface
	void CreateClientAsync(int socketfd, struct sockaddr_in newClientAddressStruct, int newClientAddressLenght) override;

	///IClientManager interface
	void RegisterClientEnded(IClientSessionManager &clientSessionManager) override;
	bool DoesSessionExistForClient(string loginname) override;

	///IClientSessionsRegister interface
	std::vector<ClientSessionView> GetAllClientSessionViews() override;
	bool EndClientSession(unsigned clientSessionViewId) override;
};

