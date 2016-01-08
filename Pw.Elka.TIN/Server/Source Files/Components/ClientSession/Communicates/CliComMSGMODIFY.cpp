#include "../../../../Header Files/Components/ClientSession/Communicates/CliComMSGMODIFY.h"



CliComMSGMODIFY::CliComMSGMODIFY(unsigned char* communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	parseShort(localBuffer); //id size, not used (always 4)	
	msgId = parseInt(localBuffer);
	msgContent = parseString(localBuffer);
	msgTitle = parseString(localBuffer);
}


CliComMSGMODIFY::~CliComMSGMODIFY()
{
}

int CliComMSGMODIFY::getMsgId()
{
	return msgId;
}
string CliComMSGMODIFY::getMsgContent()
{
	return msgContent;
}
string CliComMSGMODIFY::getMsgTitle()
{
	return msgTitle;
}
