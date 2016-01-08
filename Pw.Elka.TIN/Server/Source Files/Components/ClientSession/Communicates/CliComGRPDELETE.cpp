#include "../../../../Header Files/Components/ClientSession/Communicates/CliComGRPDELETE.h"



CliComGRPDELETE::CliComGRPDELETE(unsigned char* communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	parseShort(localBuffer); //id size, not used (always 4)	
	grpId = parseInt(localBuffer);
}


CliComGRPDELETE::~CliComGRPDELETE()
{
}

int CliComGRPDELETE::getGrpId()
{
	return grpId;
}
