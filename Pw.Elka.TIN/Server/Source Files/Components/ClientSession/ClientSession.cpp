#include "../../../Header Files/Components/ClientSession/ClientSession.h"

int DJBHash(string& str);

bool ClientSession::Start()
{
	while (true)
	{
		try {
			switch (sessionState)
			{
			case Unauthorized:
			{
				//sending an authorization communicate
				ServComAUTH* authorizationCommunicate = new ServComAUTH();	//creating communicate
				salt = authorizationCommunicate->getSalt();
				bottomLayer->Send(authorizationCommunicate->getCommunicate(), authorizationCommunicate->getSize());	//sending communicate

				bottomLayer->Receive(cliCom, comSize);
				if (cliCom[0] != _CLICOMAUTH)
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
				break;
			}

			case Authorized:
			{
				bottomLayer->Receive(cliCom, comSize); //get communicate from client
				communicateCode = cliCom[0];
				switch (communicateCode)
				{
				case _CLICOMADDRADD:
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
				case _CLICOMMSGCREATE:
				{
					CliComMSGCREATE* cliComMsgcreate = new CliComMSGCREATE(cliCom);
					communicateService(*cliComMsgcreate);
					break;
				}
				case _CLICOMADDRRMV:
				{
					CliComADDRRMV* cliComAddrrmv = new CliComADDRRMV(cliCom);
					communicateService(*cliComAddrrmv);
					break;
				}
				case _CLICOMMSGDELETE:
				{
					CliComMSGDELETE* cliComMsgdelete = new CliComMSGDELETE(cliCom);
					communicateService(*cliComMsgdelete);
					break;
				}
				case _CLICOMGRPDELETE:
				{
					CliComGRPDELETE* cliComGrpdelete = new CliComGRPDELETE(cliCom);
					communicateService(*cliComGrpdelete);
					break;
				}
				case _CLICOMMSGMODIFY:
				{
					CliComMSGMODIFY* cliComMsgmodify = new CliComMSGMODIFY(cliCom);
					communicateService(*cliComMsgmodify);
					break;
				}
				case _CLICOMGRPADRADD:
				{
					CliComGRPADRADD* cliComGrpadrad = new CliComGRPADRADD(cliCom);
					communicateService(*cliComGrpadrad);
					break;
				}
				case _CLICOMGRPADRRMV:
				{
					CliComGRPADRRMV* cliComGrpadrrm = new CliComGRPADRRMV(cliCom);
					communicateService(*cliComGrpadrrm);
					break;
				}
				case _CLICOMPSSWCHG:
				{
					CliComPSSWCHG* cliComPsswchg = new CliComPSSWCHG(cliCom);
					communicateService(*cliComPsswchg);
					break;
				}
				case _CLICOMSEND:
				{
					CliComSEND* cliComSend = new CliComSEND(cliCom);
					communicateService(*cliComSend);
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
		catch (const char* e)
		{
			if (e == "Client ended")
			{
				return 0;
			}
			if (e == "Network error")
			{
				cerr << e;
				return 1;
			}
			if (e == "WSA error")
			{
				cerr << e;
				return 2;
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

void ClientSession::communicateService(CliComAUTH clientCommunicate)
{

	ClientModel clientDB = DAL->getClient(clientCommunicate.getUsername());

	if (clientDB.blocked || clientDB.id < 0)
	{
		ServComERRLOGIN* errLogin = new ServComERRLOGIN();
		bottomLayer->Send(errLogin->getCommunicate(), errLogin->getSize());
		delete errLogin;
		return;
	}
	//password hash stored in DB
	string passwordDB = clientDB.hashOfPassword;

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


void ClientSession::communicateService(CliComADDRADD clientCommunicate)
{
	AddressModel addressDB = DAL->CreateAddress(clientCommunicate.getAddressName(), clientCommunicate.getAddressValue(), clientId);

	if (addressDB.id < 0) //error adding address -don't know what's going to be returned yet (np. adres ju¿ istnieje)
	{
		ServComERRADDR* ack = new ServComERRADDR();
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
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
	vector<AddressModel> addressVectorDB = DAL->GetAllAddresses(clientId);

	ServComADDRGETALL* ack = new ServComADDRGETALL(&addressVectorDB);
	bottomLayer->Send(ack->getCommunicate(), ack->getSize());
	delete ack;
}

void ClientSession::communicateService(CliComGRPGETALL clientCommunicate)
{
	vector<GroupModel> groupVectorDB = DAL->GetAllGroupsWithoutAdresses(clientId);

	ServComGRPGETALL* ack = new ServComGRPGETALL(&groupVectorDB);
	bottomLayer->Send(ack->getCommunicate(), ack->getSize());
	delete ack;
}

void ClientSession::communicateService(CliComMSGGETALL clientCommunicate)
{
	vector<MessageModel> messageVectorDB = DAL->GetAllMessagesWithoutContent(clientId);

	ServComMSGGETALL* ack = new ServComMSGGETALL(&messageVectorDB);
	bottomLayer->Send(ack->getCommunicate(), ack->getSize());
	delete ack;
}

void ClientSession::communicateService(CliComGRPGETONE clientCommunicate)
{
	//client's data stored in db
	GroupModel groupDB = DAL->GetGroupById(clientCommunicate.getGroupId(), clientId);

	if (groupDB.id < 0) //error adding address -don't know what's going to be returned yet (np. adres ju¿ istnieje)
	{
		ServComERRGROUP* errGroup = new ServComERRGROUP();
		bottomLayer->Send(errGroup->getCommunicate(), errGroup->getSize());
		delete errGroup;
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
	MessageModel messageDB = DAL->GetMessageById(clientCommunicate.getMessageId(), clientId);

	if (messageDB.id < 0) //error fetching a message
	{
		ServComERRMSG* errMsg = new ServComERRMSG();
		bottomLayer->Send(errMsg->getCommunicate(), errMsg->getSize());
		delete errMsg;
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
	GroupModel groupDB = DAL->CreateGroup(clientCommunicate.getGroupName(), clientId);

	if (groupDB.id < 0) //error adding address -don't know what's going to be returned yet (np. adres ju¿ istnieje)
	{
		ServComERRGROUP* errGroup = new ServComERRGROUP();
		bottomLayer->Send(errGroup->getCommunicate(), errGroup->getSize());
		delete errGroup;
	}

	else
	{
		ServComGRPGETONE* ack = new ServComGRPGETONE(&groupDB);
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}

}

void ClientSession::communicateService(CliComMSGCREATE clientCommunicate)
{
	MessageModel messageDB = DAL->CreateMessage(clientCommunicate.getMsgTitle(), clientCommunicate.getMsgContent(), clientId);

	if (messageDB.id < 0) //error creating message
	{
		ServComERRMSG* errMsg = new ServComERRMSG();
		bottomLayer->Send(errMsg->getCommunicate(), errMsg->getSize());
		delete errMsg;
	}

	else
	{
		ServComMSGGETONE* ack = new ServComMSGGETONE(&messageDB);
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}

}

void ClientSession::communicateService(CliComADDRRMV clientCommunicate)
{
	bool isDeleted = DAL->DeleteAddress(clientCommunicate.getAddrId(), clientId);

	if (isDeleted == false) //error adding address -don't know what's going to be returned yet (np. adres ju¿ istnieje)
	{
		ServComERRADDR* ack = new ServComERRADDR();
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}

	else
	{
		ServComACK* ack = new ServComACK();
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}
}

void ClientSession::communicateService(CliComMSGDELETE clientCommunicate)
{
	bool isDeleted = DAL->DeleteMessage(clientCommunicate.getMsgId(), clientId);

	if (isDeleted == false) //error adding address -don't know what's going to be returned yet (np. adres ju¿ istnieje)
	{
		ServComERRMSG* errMsg = new ServComERRMSG();
		bottomLayer->Send(errMsg->getCommunicate(), errMsg->getSize());
		delete errMsg;
	}
	else
	{
		ServComACK* ack = new ServComACK();
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}
}

void ClientSession::communicateService(CliComGRPDELETE clientCommunicate)
{
	bool isDeleted = DAL->DeleteGroupById(clientCommunicate.getGrpId(), clientId);

	if (isDeleted == false) //error deleting a group
	{
		ServComERRGROUP* errGroup = new ServComERRGROUP();
		bottomLayer->Send(errGroup->getCommunicate(), errGroup->getSize());
		delete errGroup;
	}
	else
	{
		ServComACK* ack = new ServComACK();
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}
}

void ClientSession::communicateService(CliComMSGMODIFY clientCommunicate)
{
	MessageModel messageDB = DAL->ModifyMessage(clientCommunicate.getMsgId(), clientCommunicate.getMsgTitle(), clientCommunicate.getMsgContent(), clientId);

	if (messageDB.id < 0) //error modifying a message
	{
		ServComERRMSG* errMsg = new ServComERRMSG();
		bottomLayer->Send(errMsg->getCommunicate(), errMsg->getSize());
		delete errMsg;
	}
	else
	{
		ServComACK* ack = new ServComACK();
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}
}

void ClientSession::communicateService(CliComGRPADRADD clientCommunicate)
{
	bool isAdded = DAL->AddAddressToGroup(clientCommunicate.getGrpId(), clientCommunicate.getAddrId(), clientId);
	if (isAdded == false) //error adding address 
	{
		ServComERRADDR* ack = new ServComERRADDR();
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}
	else
	{
		ServComACK* ack = new ServComACK();
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}
}

void ClientSession::communicateService(CliComGRPADRRMV clientCommunicate)
{
	bool isDeleted = DAL->RemoveAddressFromGroup(clientCommunicate.getGrpId(), clientCommunicate.getAddrId(), clientId);
	if (isDeleted == false) //error removing address 
	{
		ServComERRADDR* ack = new ServComERRADDR();
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}
	else
	{
		ServComACK* ack = new ServComACK();
		bottomLayer->Send(ack->getCommunicate(), ack->getSize());
		delete ack;
	}
}

void ClientSession::communicateService(CliComPSSWCHG clientCommunicate)
{
	ClientModel clientDB = DAL->getClient(clientName);

	if (clientDB.id < 0) //no such user -don't know what's going to be returned yet
	{
		ServComERRSERVUNAV* errUnav = new ServComERRSERVUNAV();
		bottomLayer->Send(errUnav->getCommunicate(), errUnav->getSize());
		delete errUnav;
	}
	else
	{
		//password hash stored in DB
		string passwordDB = clientDB.hashOfPassword;

		if (passwordDB == clientCommunicate.getPasswHash())
		{
			bool isChanged = DAL->ChangeHashOfPassword(clientName, clientCommunicate.getNewPasswHash());

			if (isChanged == false)
			{
				ServComERRSERVUNAV* errUnav = new ServComERRSERVUNAV();
				bottomLayer->Send(errUnav->getCommunicate(), errUnav->getSize());
				delete errUnav;
			}
			else
			{
				ServComACK* ack = new ServComACK();
				bottomLayer->Send(ack->getCommunicate(), ack->getSize());
				delete ack;
			}
		}
		else
		{
			ServComERRLOGIN* errLogin = new ServComERRLOGIN();
			bottomLayer->Send(errLogin->getCommunicate(), errLogin->getSize());
			delete errLogin;
		}
	}
}

void ClientSession::communicateService(CliComSEND clientCommunicate)
{
	GroupModel groupDB = DAL->GetGroupById(clientCommunicate.getGrpId(), clientId);
	if (groupDB.id < 0) //no such group
	{
		ServComERRGROUP* errGroup = new ServComERRGROUP();
		bottomLayer->Send(errGroup->getCommunicate(), errGroup->getSize());
		delete errGroup;
		return;
	}

	MessageModel messageDB = DAL->GetMessageById(clientCommunicate.getMsgId(), clientId);

	if (messageDB.id < 0) //no such message
	{
		ServComERRMSG* errMsg = new ServComERRMSG();
		bottomLayer->Send(errMsg->getCommunicate(), errMsg->getSize());
		delete errMsg;
		return;
	}

	vector<string> readyAddressList;
	for (unsigned int i = 0; i < groupDB.addresses.size(); ++i)
	{
		readyAddressList.push_back(groupDB.addresses[i].value);
	}

	string readyMessage = messageDB.content;
	/*
	Here should be combining a message template with the fields

	*/

	SmtpMessage smtpMessage = *new SmtpMessage(clientName, readyMessage, messageDB.title, readyAddressList);

	messagesQueue->Push(smtpMessage);
	ServComACK* ack = new ServComACK();
	bottomLayer->Send(ack->getCommunicate(), ack->getSize());
	delete ack;
}


int DJBHash(string& str)
{
	int hash = 5381;

	for (std::size_t i = 0; i < str.length(); i++)
	{
		unsigned char c = str[i];
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}