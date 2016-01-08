#pragma once
#include "Communicate.h"
//Client communicate - remove an address from all defined addresses
class CliComADDRRMV :
	public Communicate
{
public:
	CliComADDRRMV(unsigned char* communicateBuffer);
	~CliComADDRRMV();
	int getAddrId();
private:
	int addrId;
};

