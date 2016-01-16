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
	std::cout << "client-modify {old login} {login} {password} - modifies client with specified old login, by setting new login and password\n";
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
	sessionsRegister.EndClientSession(id);
}

void AdministratorView::clientsDisplay()
{
	std::vector<ClientModel> clients = DAL.GetAllClients();
	for (unsigned i = 0; i < clients.size(); ++i)
	{
		std::cout << clients[i].id << " " << clients[i].login << "\n";
	}
}

void AdministratorView::clientBlock(string login, bool isBlocked)
{
	if (isBlocked)
	{
		DAL.BlockClient(login);
	}
	else
	{
		DAL.UnblockClient(login);
	}
}

void AdministratorView::clientCreate(string login, string password)
{
	DAL.CreateClient(login, GetHashedString(password));
}

void AdministratorView::clientDelete(string login)
{
	DAL.DeleteClient(login);
}

void AdministratorView::clientSetPass(string login, string password)
{
	DAL.ChangeHashOfPassword(login, GetHashedString(password));
}

void AdministratorView::clientSetLogin(string oldLogin, string newLogin)
{
	DAL.ChangeLogin(oldLogin, newLogin);
}

string AdministratorView::GetHashedString(string str)
{/*
	unsigned char key[7] = { 143, 87, 133, 84, 123, 101, 68 };
	std::size_t minimumStringLength = 16;
	std::size_t characterLength = max(str.length(), minimumStringLength);
	unsigned char* characters = new unsigned char[characterLength];

	for (unsigned int i = 0; i < characterLength; ++i)
	{
		characters[i] = ((key[i % 7]) ^ (str[i % str.length()]));
	}

	string returnStr;
	returnStr.assign((char*)characters, characterLength);
	delete characters;
	return returnStr;*/
	return str;
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
	}
}