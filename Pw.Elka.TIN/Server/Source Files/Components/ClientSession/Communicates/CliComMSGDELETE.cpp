#include "../../../../Header Files/Components/ClientSession/Communicates/CliComMSGDELETE.h"



CliComMSGDELETE::CliComMSGDELETE(unsigned char* communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	parseShort(localBuffer); //id size, not used (always 4)	
	msgId = parseInt(localBuffer);
}


CliComMSGDELETE::~CliComMSGDELETE()
{
}

int CliComMSGDELETE::getMsgId()
{
	return msgId;
}