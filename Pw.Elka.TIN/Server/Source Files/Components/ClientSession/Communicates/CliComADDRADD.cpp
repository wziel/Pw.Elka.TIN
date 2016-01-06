#include "../../../../Header Files/Components/ClientSession/Communicates/CliComADDRADD.h"



CliComADDRADD::CliComADDRADD()
{
	throw "Class unimplemented";
}

CliComADDRADD::CliComADDRADD(unsigned char* communicateBuffer) : Communicate(communicateBuffer)
{
	addressValueSize = (((communicateBuffer[2]) << 8) | (communicateBuffer[1]));
	addressValue.assign((char*)communicateBuffer + 3, addressValueSize);
	addressNameSize = (((communicateBuffer[3+addressValueSize+1]) << 8) | (communicateBuffer[3+addressValueSize]));
	addressName.assign((char*)communicateBuffer + 3 +addressValueSize +2, addressNameSize);
}

CliComADDRADD::~CliComADDRADD()
{
}
