#pragma once

#include "../../Interfaces/IClientCreator.h"
#include "../../Interfaces/IClientManager.h"

class RootManager :
	public IClientCreator, public IClientManager
{
public:
	RootManager();
	~RootManager();
};

