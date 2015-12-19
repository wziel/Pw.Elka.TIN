#pragma once

#include "../../Interfaces/IClientSessionsRegister.h"
#include "../../Interfaces/IAdminDAL.h"


class AdministratorView
{
private:
	IClientSessionsRegister& sessionsRegister;
	IAdminDAL& DAL;

public:
	AdministratorView();
	~AdministratorView();

	void Initialize(IClientSessionsRegister& sessionsRegister, IAdminDAL& DAL);
	void Start();
	
};