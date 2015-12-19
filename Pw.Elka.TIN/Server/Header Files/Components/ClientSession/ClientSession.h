#pragma once
#include "../../Interfaces/IClientSessionManager.h"

class ClientSession : 
	public IClientSessionManager
{
public:
	ClientSession();
	~ClientSession();
};

