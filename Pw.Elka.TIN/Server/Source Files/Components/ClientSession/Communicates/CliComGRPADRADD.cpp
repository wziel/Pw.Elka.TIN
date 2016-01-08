#include "../../../../Header Files/Components/ClientSession/Communicates/CliComGRPADRADD.h"



CliComGRPADRADD::CliComGRPADRADD(unsigned char* communicateBuffer) : Communicate(communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	parseShort(localBuffer); //id size, not used (always 4)	
	grpId = parseInt(localBuffer);
	parseShort(localBuffer); //id size, not used (always 4)	
	addrId = parseInt(localBuffer);
}


CliComGRPADRADD::~CliComGRPADRADD()
{
}

int CliComGRPADRADD::getGrpId()
{
	return grpId;
}
int CliComGRPADRADD::getAddrId()
{
	return addrId;
}