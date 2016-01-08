#include "../../../../Header Files/Components/ClientSession/Communicates/CliComADDRADD.h"



CliComADDRADD::CliComADDRADD()
{
	throw "Class unimplemented";
}

CliComADDRADD::CliComADDRADD(unsigned char* communicateBuffer) : Communicate(communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	addressValue = parseString(localBuffer);
	addressName = parseString(localBuffer);
}

CliComADDRADD::~CliComADDRADD()
{
}

string CliComADDRADD::getAddressValue()
{
	return addressValue;
}
string CliComADDRADD::getAddressName()
{
	return addressName;
}