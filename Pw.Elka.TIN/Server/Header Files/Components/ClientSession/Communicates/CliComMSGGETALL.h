#pragma once
#include "Communicate.h"
//Client communicate - request getting all message schemes names
class CliComMSGGETALL :
	public Communicate
{
public:
	CliComMSGGETALL(unsigned char* communicateBuffer);
	~CliComMSGGETALL();
};

