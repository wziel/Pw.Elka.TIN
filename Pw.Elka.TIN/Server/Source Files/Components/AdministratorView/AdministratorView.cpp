#include "..\..\..\Header Files\Components\AdministratorView\AdministratorView.h"
#include <iostream>
#include <algorithm>
#include<iomanip>

AdministratorView::AdministratorView(IClientSessionsRegister& sessionsRegister, IAdminDAL& DALarg) : DAL(DALarg), sessionsRegister(sessionsRegister)
{
}


AdministratorView::~AdministratorView()
{
}

void AdministratorView::Start()
{
	helpDisplay();
	mainLoop();
}

void AdministratorView::helpDisplay()
{
	std::cout << "Commands:\n";
	std::cout << "help - displays help\n";
	std::cout << "sessions - lists all sessions\n";
	std::cout << "session-end {id} - ends session of specified id\n";
	std::cout << "clients - lists all clients\n";
	std::cout << "client-block {login} - blocks client of specified login\n";
	std::cout << "client-unblock {login} - unblocks clients with specified login\n";
	std::cout << "client-create {login} {password} - creates client with specified login and password\n";
	std::cout << "client-delete {login} - delets client with specified login\n";
	std::cout << "client-pass {login} {password} - modifies password of client with specified login\n";
	std::cout << "client-login {old login} {login} - modifies client with specified old login, by setting new login\n";
	std::cout << "exit - exit the programm\n";
}

void AdministratorView::sessionsDisplay()
{
	std::vector <ClientSessionView> views = sessionsRegister.GetAllClientSessionViews();
	if (views.size() == 0)
	{
		std::cout << "There are currently no sessions\n";
		return;
	}
	std::cout << setw(20) << "Connection ID" << setw(20) << "Connection state" << setw(20) << "Client Name\n";
	for (unsigned i = 0; i < views.size(); ++i)
	{
		std::cout << setw(20) << views[i].connectionId << setw(20) << views[i].state << setw(20) << views[i].clientName;
		std::cout << "\n";
	}
}

void AdministratorView::sessionEnd(unsigned id)
{
	if (sessionsRegister.EndClientSession(id))
	{
		std::cout << "Successfully ended client session.\n";
	}
	else
	{
		std::cout << "Specified session wasn't found.\n";
	}
}

void AdministratorView::clientsDisplay()
{
	std::vector<ClientModel> clients = DAL.GetAllClients();
	if (clients.size() == 0)
	{
		std::cout << "There are no clients in database.\n";
		return;
	}
	std::cout << setw(20) << "Client ID" << setw(20) << "Client login" << setw(20) << "Is client blocked\n";
	for (unsigned i = 0; i < clients.size(); ++i)
	{
		std::cout << setw(20) << clients[i].id << setw(20) << clients[i].login << setw(20) << (clients[i].blocked ? "Blocked" : "Not blocked");
		std::cout << "\n";
	}
}

void AdministratorView::clientBlock(string login, bool isBlocked)
{
	if (isBlocked)
	{
		if (DAL.BlockClient(login))
		{
			std::cout << "Successfully blocked client.\n";
		}
		else
		{
			std::cout << "Failed to block client.\n";
		}
	}
	else
	{
		if (DAL.UnblockClient(login))
		{
			std::cout << "Successfully unblocked client.\n";
		}
		else
		{
			std::cout << "Failed to unblock client.\n";
		}
	}
}

void AdministratorView::clientCreate(string login, string password)
{
	if (DAL.CreateClient(login, GetObfuscatedString(password)))
	{
		std::cout << "Successfully created client.\n";
	}
	else
	{
		std::cout << "Failed to create client.\n";
	}
}

void AdministratorView::clientDelete(string login)
{
	std::vector <ClientSessionView> views = sessionsRegister.GetAllClientSessionViews();
	for (unsigned int i = 0; i < views.size(); ++i)
	{
		if (views[i].clientName == login)
		{
			sessionsRegister.EndClientSession(views[i].connectionId);
		}
	}
	if (DAL.DeleteClient(login))
	{
		std::cout << "Successfully deleted client.\n";
	}
	else
	{
		std::cout << "Failed to delete client.\n";
	}
}

void AdministratorView::clientSetPass(string login, string password)
{
	if (DAL.ChangeHashOfPassword(login, GetObfuscatedString(password)))
	{
		std::cout << "Successfully changed client password.\n";
	}
	else
	{
		std::cout << "Failed to change client password.\n";
	}
}

void AdministratorView::clientSetLogin(string oldLogin, string newLogin)
{
	if (DAL.ChangeLogin(oldLogin, newLogin))
	{
		std::cout << "Successfully changed client login.\n";
	}
	else
	{
		std::cout << "Failed to change client login.\n";
	}
}

string AdministratorView::GetObfuscatedString(string str)
{
	unsigned char key[7] = { 143, 87, 133, 84, 123, 101, 68 };
	std::size_t minimumStringLength = 32;
	std::size_t characterLength = max(str.length(), minimumStringLength);
	string returnStr = "";
	int summedChars = 5381;

	for (unsigned int i = 0; i < characterLength; ++i)
	{
		unsigned char c = ((key[i % 7]) ^ (str[i % str.length()]));
		summedChars += (int)c;
		char toAppend = (char)('0' + (summedChars % 10));

		returnStr.append(1, toAppend);
	}

	return returnStr;
}

void AdministratorView::mainLoop()
{
	string command;
	string login;
	string password;
	string oldLogin;
	int id;
	while (true)
	{
		std::cin >> command;
		if (command == "help")
		{
			helpDisplay();
		}
		else if (command == "sessions")
		{
			sessionsDisplay();
		}
		else if (command == "session-end")
		{
			std::cin >> id;
			sessionEnd(id);
		}
		else if (command == "clients")
		{
			clientsDisplay();
		}
		else if (command == "client-block")
		{
			std::cin >> login;
			clientBlock(login, true);
		}
		else if (command == "client-unblock")
		{
			std::cin >> login;
			clientBlock(login, false);
		}
		else if (command == "client-create")
		{
			std::cin >> login >> password;
			clientCreate(login, password);
		}
		else if (command == "client-delete")
		{
			std::cin >> oldLogin;
			clientDelete(oldLogin);
		}
		else if (command == "client-pass")
		{
			std::cin >> login >> password;
			clientSetPass(login, password);
		}
		else if (command == "client-login")
		{
			std::cin >> oldLogin >> login;
			clientSetLogin(oldLogin, login);
		}
		else if (command == "exit")
		{
			return;
		}
		else
		{
			std::cout << "Command unknown.\n";
		}
	}
}