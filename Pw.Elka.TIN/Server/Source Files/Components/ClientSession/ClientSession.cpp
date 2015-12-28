#include "../../../Header Files/Components/ClientSession/ClientSession.h"



bool ClientSession::Start()
{
	//sending an authorization communicate
	ServComAUTH* authorizationCommunicate = new ServComAUTH();	//creating communicate
	salt = authorizationCommunicate->getSalt();
	bottomLayer->Send(authorizationCommunicate->getCommunicate(), authorizationCommunicate->getSize());	//sending communicate

	while (true)
	{
		switch (sessionState)
		{

		case Unauthorized:
		{	


			throw "Unimplemented";
			break;
		}

		case Authorized:
		{
			throw "Unimplemented";
			break;
		}
	
		case Busy:
		{
			throw "Unimplemented";
			break;
		}
		default:
		{
			throw "Server state error";
		}

		}
	}
}


bool ClientSession::Initialize(ILayer &bottomLayer, MessagesQueue &queue, SessionState initialState, IClientDAL &DAL, IClientManager &clientManager)
{
	this->bottomLayer = &bottomLayer;
	this->messagesQueue = &queue;
	this->sessionState = initialState;
	this->DAL = &DAL;
	this->clientManager = &clientManager;

	return true;
}

string ClientSession::GetClientName()
{
	return clientName;
}


ClientSession::ClientSession()
{
}


ClientSession::~ClientSession()
{
}
