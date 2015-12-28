#pragma once
#include "Communicate.h"
//Server communicate - sending salt needed for hashing a password
class ServComAUTH :
	public Communicate
{
public:
	ServComAUTH();
	~ServComAUTH();
};

