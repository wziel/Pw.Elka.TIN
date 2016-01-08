#include "../../../Header Files/Components/ClientSession/ClientSession.h"

int DJBHash(string& str);

bool ClientSession::Start()
{
	while (true)
	{
		switch (sessionState)
		{

		case Unauthorized:
		{
			//sending an authorization communicate
			ServComAUTH* authorizationCommunicate = new ServComAUTH();	//creating communicate
			salt = authorizationCommunicate->getSalt();
			bottomLayer->Send(authorizationCommunicate->getCommunicate(), authorizationCommunicate->getSize());	//sending communicate

			bottomLayer->Receive(cliCom, comSize);
			if (cliCom[0]!= _CLICOMAUTH)
			{	//client sent anything else than CliComAuth 
				ServComERRUNAUTH* servUnauth = new ServComERRUNAUTH();		//tell client he is not authorized
				bottomLayer->Send(servUnauth->getCommunicate(), servUnauth->getSize());
				delete servUnauth;
			}
			else
			{
				CliComAUTH* cliComAuth = new CliComAUTH(cliCom);
				communicateService(*cliComAuth);
			}
			//throw "Unimplemented";
			break;
		}

		case Authorized:
		{
			bottomLayer->Receive(cliCom, comSize);
			communicateCode = cliCom[0];
			switch (communicateCode)
			{
			case _CLICOMADDRADD :
			{
				CliComADDRADD* cliComAddradd = new CliComADDRADD(cliCom);
				communicateService(*cliComAddradd);
				break;
			}

			case _CLICOMADDRGETALL:
			{
				CliComADDRGETALL* cliComAddrgetall = new CliComADDRGETALL(cliCom);
				communicateService(*cliComAddrgetall);
				break;
			}

			case _CLICOMGRPGETALL:
			{
				CliComGRPGETALL* cliComGrprgetall = new CliComGRPGETALL(cliCom);
				communicateService(*cliComGrprgetall);
				break;
			}

			case _CLICOMMSGGETALL:
			{
				CliComMSGGETALL* cliComMsggetall = new CliComMSGGETALL(cliCom);
				communicateService(*cliComMsggetall);
				break;
			}

			case _CLICOMGRPGETONE:
			{
				CliComGRPGETONE* cliComGrpgetone = new CliComGRPGETONE(cliCom);
				communicateService(*cliComGrpgetone);
				break;
			}

			case _CLICOMMSGGETONE:
			{
				CliComMSGGETONE* cliComMsggetone = new CliComMSGGETONE(cliCom);
				communicateService(*cliComMsggetone);
				break;
			}

			case _CLICOMGRPCREATE:
			{
				CliComGRPCREATE* cliComGrpcreate = new CliComGRPCREATE(cliCom);
				communicateService(*cliComGrpcreate);
				break;
			}

			default:
			{
				//No such communicate code
				ServComERRBADREQ* badReq = new ServComERRBADREQ();	
				bottomLayer->Send(badReq->getCommunicate(), badReq->getSize());
				delete badReq;
				break;
			}

			}

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

ClientSession::ClientSession(ILayer &bottomLayer, MessagesQueue &queue, SessionState initialState, IClientDAL &DAL, IClientManager &clientManager)
{
	this->bottomLayer = &bottomLayer;
	this->messagesQueue = &queue;
	this->sessionState = initialState;
	this->DAL = &DAL;
	this->clientManager = &clientManager;
}

string ClientSession::GetClientName()
{
	return clientName;
}

ClientSession::~ClientSession()
{
}

void ClientSession:: communicateService(CliComAUTH clientCommunicate)
{
	//client's data stored in db
	ClientModel clientDB = DAL->getClient(clientCommunicate.getUsername());

	if (0) //no such user -don't know what's going to be returned yet
	{
		ServComERRLOGIN* errLogin = new ServComERRLOGIN();
		bottomLayer->Send(errLogin->getCommunicate(), errLogin->getSize());
		delete errLogin;
	}
	
	else
	{
		//password hash stored in DB
		string passwordDB = clientDB.hashOfPassword;
		//string passwordDB=DAL->GetHashOfPassword(clientCommunicate.getUsername());

		passwordDB.append(salt);
		
		//(password hash + salt) hash, (based on DB values)
		int passwordhashDB = DJBHash(passwordDB);

		if (passwordhashDB == clientCommunicate.getpasswHashAuth())
		{
			clientName = clientCommunicate.getUsername();
			clientId = clientDB.id;
			ServComACK* ack = new ServComACK();
			bottomLayer->Send(ack->getCommunicate(), ack->getSize());
			sessionState = Authorized;
			delete ack;
		}
		else
		{
			ServComERRLOGIN* errLogin = new ServComERRLOGIN();
			bottomLayer->Send(errLogin->getCommunicate(), errLogin->getSize());
			delete errLogin;
		}
	}

}

void ClientSession::communicateService(CliComADDRADD clientCommunicate)
{
	//client's data stored in db
	AddressModel addressDB = DAL->CreateAddress(clientCommunicate.getAddressName(), clientCommunicate.getAddressValue(), clientId);

	if (0) //error adding address -don't know what's going to be returned yet (np. adres ju� istnieje)
	{
	}

	else
	{
		ServComADDRGETONE* ack = new ServComADDRGETONE(addressDB.id);
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}

}

void ClientSession::communicateService(CliComADDRGETALL clientCommunicate)
{
	//client's data stored in db
	vector<AddressModel> addressVectorDB = DAL->GetAllAddresses(clientId);

	if (0) //error  -don't know what's going to be returned yet (np. adres ju� istnieje)
	{
	}

	else
	{
		ServComADDRGETALL* ack = new ServComADDRGETALL(&addressVectorDB);
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}

}

void ClientSession::communicateService(CliComGRPGETALL clientCommunicate)
{
	//client's data stored in db
	vector<GroupModel> groupVectorDB = DAL->GetAllGroupsWithoutAdresses(clientId);

	if (0) //error  -don't know what's going to be returned yet (np. adres ju� istnieje)
	{
	}

	else
	{
		ServComGRPGETALL* ack = new ServComGRPGETALL(&groupVectorDB);
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}

}

void ClientSession::communicateService(CliComMSGGETALL clientCommunicate)
{
	//client's data stored in db
	vector<MessageModel> messageVectorDB = DAL->GetAllMessagesWithoutContent(clientId);

	if (0) //error  -don't know what's going to be returned yet (np. adres ju� istnieje)
	{
	}

	else
	{
		ServComMSGGETALL* ack = new ServComMSGGETALL(&messageVectorDB);
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}

}

void ClientSession::communicateService(CliComGRPGETONE clientCommunicate)
{
	//client's data stored in db
	GroupModel groupDB = DAL->GetGroupById(clientCommunicate.getGroupId(),clientId);

	if (0) //error adding address -don't know what's going to be returned yet (np. adres ju� istnieje)
	{
	}

	else
	{
		ServComGRPGETONE* ack = new ServComGRPGETONE(&groupDB);
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}

}

void ClientSession::communicateService(CliComMSGGETONE clientCommunicate)
{
	//client's data stored in db
	MessageModel messageDB = DAL->GetMessageById(clientCommunicate.getMessageId(), clientId);

	if (0) //error adding address -don't know what's going to be returned yet (np. adres ju� istnieje)
	{
	}

	else
	{
		ServComMSGGETONE* ack = new ServComMSGGETONE(&messageDB);
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}

}

void ClientSession::communicateService(CliComGRPCREATE clientCommunicate)
{
	//client's data stored in db
	GroupModel groupDB = DAL->CreateGroup(clientCommunicate.getGroupName(), clientId);

	if (0) //error adding address -don't know what's going to be returned yet (np. adres ju� istnieje)
	{
	}

	else
	{
		ServComGRPGETONE* ack = new ServComGRPGETONE(&groupDB);
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}

}

int DJBHash(string& str)
{
	unsigned int hash = 5381;

	for (std::size_t i = 0; i < str.length(); i++)
	{
		hash = ((hash << 5) + hash) + str[i];
	}

	return hash;
}