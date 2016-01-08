#include "../../../../Header Files/Components/ClientSession/Communicates/CliComGRPGETONE.h"



CliComGRPGETONE::CliComGRPGETONE(unsigned char* communicateBuffer) : Communicate(communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	parseShort(localBuffer); //group id size, not used (always 4)	
	groupId = parseInt(localBuffer);
}


CliComGRPGETONE::~CliComGRPGETONE()
{
}

int CliComGRPGETONE::getGroupId()
{
	return groupId;
}
