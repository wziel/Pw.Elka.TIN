#include "../../../../Header Files/Components/ClientSession/Communicates/CliComMSGGETONE.h"



CliComMSGGETONE::CliComMSGGETONE(unsigned char* communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	parseShort(localBuffer); //message id size, not used (always 4)	
	messageId = parseInt(localBuffer);
}


CliComMSGGETONE::~CliComMSGGETONE()
{
}

int CliComMSGGETONE::getMessageId()
{
	return messageId;
}