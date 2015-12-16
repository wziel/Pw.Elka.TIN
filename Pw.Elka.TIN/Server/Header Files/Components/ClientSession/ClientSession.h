#pragma once
#include "../../Interfaces/IClientSession.h"
#include "../../Interfaces/IClientSessionManager.h"

class ClientSession :
	public IClientSession, public IClientSessionManager
{
public:
	ClientSession();
	~ClientSession();
};

