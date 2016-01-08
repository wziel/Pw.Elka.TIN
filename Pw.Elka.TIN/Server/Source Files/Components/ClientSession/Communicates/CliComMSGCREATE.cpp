#include "../../../../Header Files/Components/ClientSession/Communicates/CliComMSGCREATE.h"



CliComMSGCREATE::CliComMSGCREATE(unsigned char* communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	msgContent = parseString(localBuffer);
	msgTitle = parseString(localBuffer);
}


CliComMSGCREATE::~CliComMSGCREATE()
{
}

string CliComMSGCREATE::getMsgContent()
{
	return msgContent;
}
string CliComMSGCREATE::getMsgTitle()
{
	return msgTitle;
}