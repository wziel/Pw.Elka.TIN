#pragma once
#include "Communicate.h"
//Server error communicate - no such message scheme
class ServComERRMSG :
	public Communicate
{
public:
	ServComERRMSG();
	~ServComERRMSG();
};

