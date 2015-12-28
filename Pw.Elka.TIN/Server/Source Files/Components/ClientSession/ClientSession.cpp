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
	while (true)
	{
		switch (sessionState)
		{
		case Authorized:
		{
			throw "Unimplemented";
			break;
		}
		case Unauthorized:
		{
			throw "Unimplemented";
			break;
		}
		case Busy:
		{
			throw "Unimplemented";
			break;
		}

		}

	}
	
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
