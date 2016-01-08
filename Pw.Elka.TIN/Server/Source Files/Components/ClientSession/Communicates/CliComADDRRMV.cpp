#include "../../../../Header Files/Components/ClientSession/Communicates/CliComADDRRMV.h"


CliComADDRRMV::CliComADDRRMV(unsigned char* communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	parseShort(localBuffer); //id size, not used (always 4)	
	addrId = parseInt(localBuffer);
}


CliComADDRRMV::~CliComADDRRMV()
{
}


int CliComADDRRMV::getAddrId()
{
	return addrId;
}