#pragma once

#include "../Components/AdministratorView/ClientSessionView.h"

class IClientSessionsRegister
{
public:
	virtual ~IClientSessionsRegister() = 0;
	virtual std::vector<ClientSessionView> GetAllClientSessionViews() = 0;
	virtual void EndClientSession(unsigned clientSessionViewId) = 0;
};