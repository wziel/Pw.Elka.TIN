#include "../../../../Header Files/Components/ClientSession/Communicates/CliComAUTH.h"

CliComAUTH::CliComAUTH(unsigned char* communicateBuffer) : Communicate(communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	username = parseString(localBuffer);
	short passwHashSize = parseShort(localBuffer); //ignore, always should be 4 (for int)
	passwHashAuth = parseInt(localBuffer);
}


CliComAUTH::~CliComAUTH()
{
}

string CliComAUTH::getUsername()
{
	return username;
}
int  CliComAUTH:: getpasswHashAuth()
{
	return passwHashAuth;
}
