#pragma once
#include "Communicate.h"
//Client Communicate - remove an address from a group
class CliComGRPADRRMV :
	public Communicate
{
public:
	CliComGRPADRRMV(unsigned char* communicateBuffer);
	~CliComGRPADRRMV();
	int getGrpId();
	int getAddrId();
private:
	int grpId;
	int addrId;

};

