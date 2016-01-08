#pragma once
#include "Communicate.h"
#include "../../../Shared/AddressModel.h"
#include <vector>

//Server communicate - sending all addresses
class ServComADDRGETALL :
	public Communicate
{
public:
	ServComADDRGETALL(vector<AddressModel>* addrVect);
	~ServComADDRGETALL();
};

