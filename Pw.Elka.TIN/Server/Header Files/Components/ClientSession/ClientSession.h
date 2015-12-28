#pragma once
#include "../../Interfaces/IClientSessionManager.h"
#include "../../Shared/SessionState.h"

//communicates
#include "../../Components/ClientSession/Communicates/CliComADDRADD.h"




using namespace std;

class ClientSession :
	public IClientSessionManager
{
public:

	// IClientSessionManager
	bool Initialize(ILayer &bottomLayer, MessagesQueue &queue, SessionState initialState, IClientDAL &DAL, IClientManager &clientManager);
	bool Start();
	string GetClientName();

	ClientSession();
	~ClientSession();

private:
	// Bottom layer for sending and receiving messages
	ILayer* bottomLayer;
	// Message queue for sending client's messages
	MessagesQueue* messagesQueue;
	//Current state of client session
	SessionState sessionState;
	// Data Access Layer
	IClientDAL* DAL;
	//Client Manager interface (used to register client ended)
	IClientManager* clientManager;
	//last communicate code
	unsigned char communicateCode; 
};
