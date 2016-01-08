#pragma once
#include "Communicate.h"
//Client communicate - request deleting a group
class CliComGRPDELETE :
	public Communicate
{
public:
	CliComGRPDELETE(unsigned char* communicateBuffer);
	~CliComGRPDELETE();
	int getGrpId();
private:
	int grpId;
};

