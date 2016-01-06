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
			//case _CLICOMADDRADD :
			//{
			//	CliComADDRADD* cliComAddradd = new CliComADDRADD(cliCom);
			////	communicateService(*cliComAddradd);
			//}

			default:
			{
				//No such communicate code
				ServComERRBADREQ* badReq = new ServComERRBADREQ();	
				bottomLayer->Send(badReq->getCommunicate(), badReq->getSize());
				delete badReq;
			}
			{

			}
			}
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

int DJBHash(string& str)
{
	unsigned int hash = 5381;

	for (std::size_t i = 0; i < str.length(); i++)
	{
		hash = ((hash << 5) + hash) + str[i];
	}

	return hash;
}