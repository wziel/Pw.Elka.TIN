#pragma once
#include "Communicate.h"
//Client communicate - add address to a group
class CliComGRPADRADD :
	public Communicate
{
public:
	CliComGRPADRADD(unsigned char* communicateBuffer);
	~CliComGRPADRADD();
	int getGrpId();
	int getAddrId();
private:
	int grpId;
	int addrId;
	
};

