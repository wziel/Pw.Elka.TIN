#include "../../../../Header Files/Components/ClientSession/Communicates/CliComAUTH.h"

CliComAUTH::CliComAUTH()
{
	throw "Class unimplemented";
}
CliComAUTH::CliComAUTH(unsigned char* communicateBuffer) : Communicate(communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	//usernameLength = parseShort(localBuffer);
	username = parseString(localBuffer);
	short passwHashSize = parseShort(localBuffer); //ignore, always should be 4 (for int)
	passwHashAuth = parseInt(localBuffer);

	//usernameLength = (((communicateBuffer[2]) << 8) | (communicateBuffer[1]));
	//username.assign((char*)communicateBuffer+3, usernameLength);
	//passwHashAuth = (communicateBuffer[3 + usernameLength + 5] << 24 | communicateBuffer[3 + usernameLength + 4] << 16 | communicateBuffer[3 + usernameLength + 3] << 8 | communicateBuffer[3 + usernameLength + 2]);
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
