#pragma once
#include "Communicate.h"

//Client communicate - request creating a group
class CliComGRPCREATE :
	public Communicate
{
public:
	CliComGRPCREATE(unsigned char* communicateBuffer);
	~CliComGRPCREATE();
	string getGroupName();
private:
	string groupName;
};

