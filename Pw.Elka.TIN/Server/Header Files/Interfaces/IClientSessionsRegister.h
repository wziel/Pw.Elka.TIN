#pragma once

#include <vector>
#include "../Components/AdministratorView/ClientSessionView.h"

class IClientSessionsRegister
{
public:
	virtual ~IClientSessionsRegister() { };
	virtual std::vector<ClientSessionView> GetAllClientSessionViews() = 0;
	virtual bool EndClientSession(unsigned clientSessionViewId) = 0;
};