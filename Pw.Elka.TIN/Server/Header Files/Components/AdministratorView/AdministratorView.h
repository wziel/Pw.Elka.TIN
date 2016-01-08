#pragma once

#include "../../Interfaces/IClientSessionsRegister.h"
#include "../../Interfaces/IAdminDAL.h"
#include<string>

class AdministratorView
{
private:
	IClientSessionsRegister& sessionsRegister;
	IAdminDAL& DAL;

	void helpDisplay();
	void sessionsDisplay();
	void sessionEnd(unsigned id);
	void clientsDisplay();
	void clientBlock(string login, bool isBlocked);
	void clientCreate(string login, string password);
	void clientDelete(string login);
	void clientSetPass(string login, string password);
	void clientSetLogin(string oldLogin, string newLogin);
	static string GetHashedString(string str);

	void mainLoop();

public:
	AdministratorView(IClientSessionsRegister& sessionsRegister, IAdminDAL& DALarg);
	~AdministratorView();

	void Start();
};