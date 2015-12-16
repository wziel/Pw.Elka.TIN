#pragma once
#include "../../Interfaces/ILayer.h"
#include "../../Interfaces/ICipherManager.h"

class Cipher :
	public ILayer, public ICipherManager
{
public:
	Cipher();
	~Cipher();
};

