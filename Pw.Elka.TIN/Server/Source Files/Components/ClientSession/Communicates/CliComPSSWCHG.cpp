#include "../../../../Header Files/Components/ClientSession/Communicates/CliComPSSWCHG.h"



CliComPSSWCHG::CliComPSSWCHG(unsigned char* communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	
	passwHash = parseString(localBuffer);
	newPasswHash = parseString(localBuffer);

}

CliComPSSWCHG::~CliComPSSWCHG()
{
}

string CliComPSSWCHG::getPasswHash()
{
	return passwHash;
}
string CliComPSSWCHG::getNewPasswHash()
{
	return newPasswHash;
}
