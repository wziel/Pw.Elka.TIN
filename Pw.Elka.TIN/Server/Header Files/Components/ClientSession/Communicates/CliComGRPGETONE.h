#pragma once
#include "Communicate.h"
//Client communicate - request getting one group
class CliComGRPGETONE :
	public Communicate
{
public:
	CliComGRPGETONE(unsigned char* communicateBuffer);
	~CliComGRPGETONE();
	int getGroupId();
private:
	int groupId;
};

