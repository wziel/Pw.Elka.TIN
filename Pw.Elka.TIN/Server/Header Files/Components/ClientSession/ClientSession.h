#pragma once
#include "../../Interfaces/IClientSessionManager.h"
#include "../../Shared/SessionState.h"
#include "../../Interfaces/ILayer.h"
#include "../../Interfaces/IClientDAL.h"

#include <string>

//communicates
#include "../../Components/ClientSession/Communicates/CliComADDRADD.h"
#include "../../Components/ClientSession/Communicates/CliComADDRGETALL.h"
#include "../../Components/ClientSession/Communicates/CliComADDRRMV.h"
#include "../../Components/ClientSession/Communicates/CliComAUTH.h"
#include "../../Components/ClientSession/Communicates/CliComGRPADRADD.h"
#include "../../Components/ClientSession/Communicates/CliComGRPADRRMV.h"
#include "../../Components/ClientSession/Communicates/CliComGRPCREATE.h"
#include "../../Components/ClientSession/Communicates/CliComGRPDELETE.h"
#include "../../Components/ClientSession/Communicates/CliComGRPGETALL.h"
#include "../../Components/ClientSession/Communicates/CliComGRPGETONE.h"
#include "../../Components/ClientSession/Communicates/CliComMSGCREATE.h"
#include "../../Components/ClientSession/Communicates/CliComMSGDELETE.h"
#include "../../Components/ClientSession/Communicates/CliComMSGGETALL.h"
#include "../../Components/ClientSession/Communicates/CliComMSGGETONE.h"
#include "../../Components/ClientSession/Communicates/CliComMSGMODIFY.h"
#include "../../Components/ClientSession/Communicates/CliComPSSWCHG.h"
#include "../../Components/ClientSession/Communicates/CliComSEND.h"
#include "../../Components/ClientSession/Communicates/ServComACK.h"
#include "../../Components/ClientSession/Communicates/ServComADDRGETALL.h"
#include "../../Components/ClientSession/Communicates/ServComADDRGETONE.h"
#include "../../Components/ClientSession/Communicates/ServComAUTH.h"
#include "../../Components/ClientSession/Communicates/ServComERRBADCONTENT.h"
#include "../../Components/ClientSession/Communicates/ServComERRBADREQ.h"
#include "../../Components/ClientSession/Communicates/ServComERRBUSY.h"
#include "../../Components/ClientSession/Communicates/ServComERRGROUP.h"
#include "../../Components/ClientSession/Communicates/ServComERRLOGIN.h"
#include "../../Components/ClientSession/Communicates/ServComERRMSG.h"
#include "../../Components/ClientSession/Communicates/ServComERRSERVUNAV.h"
#include "../../Components/ClientSession/Communicates/ServComERRUNAUTH.h"
#include "../../Components/ClientSession/Communicates/ServComGRPGETALL.h"
#include "../../Components/ClientSession/Communicates/ServComGRPGETONE.h"
#include "../../Components/ClientSession/Communicates/ServComMSGGETALL.h"
#include "../../Components/ClientSession/Communicates/ServComMSGGETONE.h"




using namespace std;

class ClientSession :
	public IClientSessionManager
{
public:

	// IClientSessionManager
//	bool Initialize(ILayer &bottomLayer, MessagesQueue &queue, SessionState initialState, IClientDAL &DAL, IClientManager &clientManager);
	bool Start();
	string GetClientName();

	ClientSession();
	ClientSession(ILayer &bottomLayer, MessagesQueue &queue, SessionState initialState, IClientDAL &DAL, IClientManager &clientManager);
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
	//last server communicate content
	char* servCom;
	//last client communicate content
	char* cliCom;
	//last communicate size
	int comSize;
	//client's username
	string clientName; 
	//salt used for hashing user's password
	string salt;

	//communicates service functions
	void communicateService(CliComAUTH clientCommunicate);
};
