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
	void clientModify(string oldLogin, string login, string password);
	static string GetHashedString(string str);

	void mainLoop();

public:
	AdministratorView();
	~AdministratorView();

	void Initialize(IClientSessionsRegister& sessionsRegister, IAdminDAL& DAL);
	void Start();
};