#pragma once
#include "Communicate.h"
//Server error communicate - too many users connected
class ServComERRBUSY :
	public Communicate
{
public:
	ServComERRBUSY();
	~ServComERRBUSY();
};

