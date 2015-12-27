#include "../../../Header Files/Components/ClientSession/ClientSession.h"

bool ClientSession::Initialize(ILayer &bottomLayer, MessagesQueue &queue, SessionState initialState, IClientDAL &DAL, IClientManager &clientManager)
{
	this->bottomLayer = &bottomLayer;
	this->messagesQueue = &queue;
	this->sessionState = initialState;
	this->DAL = &DAL;
	this->clientManager = &clientManager;

	return true; 
}

bool ClientSession::Start()
{
	throw "Unimplemented";
}
string ClientSession::GetClientName()
{
	throw "Unimplemented";
}



ClientSession::ClientSession()
{
}


ClientSession::~ClientSession()
{
}
