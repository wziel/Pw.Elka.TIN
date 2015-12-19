#include "..\..\..\Header Files\Components\AdministratorView\AdministratorView.h"



AdministratorView::AdministratorView()
{
}


AdministratorView::~AdministratorView()
{
}

void AdministratorView::Initialize(IClientSessionsRegister& sessionsRegister, IAdminDAL& DAL)
{
	this->DAL = DAL;
	this->sessionsRegister = sessionsRegister;
}

void AdministratorView::Start()
{

}