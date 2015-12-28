#pragma once
#include "Communicate.h"
//Server error communicate - client not authorized
class ServComERRUNAUTH :
	public Communicate
{
public:
	ServComERRUNAUTH();
	~ServComERRUNAUTH();
};

