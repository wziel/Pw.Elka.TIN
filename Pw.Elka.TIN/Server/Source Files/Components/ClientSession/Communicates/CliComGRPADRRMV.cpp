#include "../../../../Header Files/Components/ClientSession/Communicates/CliComGRPADRRMV.h"



CliComGRPADRRMV::CliComGRPADRRMV(unsigned char* communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	parseShort(localBuffer); //id size, not used (always 4)	
	grpId = parseInt(localBuffer);
	parseShort(localBuffer); //id size, not used (always 4)	
	addrId = parseInt(localBuffer);
}


CliComGRPADRRMV::~CliComGRPADRRMV()
{
}

int CliComGRPADRRMV::getGrpId()
{
	return grpId;
}
int CliComGRPADRRMV::getAddrId()
{
	return addrId;
}