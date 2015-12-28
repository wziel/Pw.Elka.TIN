#pragma once
#include "Communicate.h"
//Server communicate - acknowledge previous client request
class ServComACK :
	public Communicate
{
public:
	ServComACK();
	~ServComACK();
};

