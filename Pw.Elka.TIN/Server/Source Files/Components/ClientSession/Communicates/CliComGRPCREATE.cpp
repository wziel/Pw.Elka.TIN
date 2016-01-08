#include "../../../../Header Files/Components/ClientSession/Communicates/CliComGRPCREATE.h"



CliComGRPCREATE::CliComGRPCREATE(unsigned char* communicateBuffer) : Communicate(communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	groupName = parseString(localBuffer);
}


CliComGRPCREATE::~CliComGRPCREATE()
{
}

string CliComGRPCREATE::getGroupName()
{
	return groupName;
}