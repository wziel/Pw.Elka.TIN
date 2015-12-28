#pragma once
#include "Communicate.h"
//Server error communicate - login or password mismatch
class ServComERRLOGIN :
	public Communicate
{
public:
	ServComERRLOGIN();
	~ServComERRLOGIN();
};

