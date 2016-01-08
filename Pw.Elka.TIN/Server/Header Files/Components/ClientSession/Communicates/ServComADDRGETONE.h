#pragma once
#include "Communicate.h"
//Server communicate - sending one address
class ServComADDRGETONE :
	public Communicate
{
public:
	ServComADDRGETONE(int addressId);
	~ServComADDRGETONE();
};

