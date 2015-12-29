#include "../../../../Header Files/Components/ClientSession/Communicates/ServComACK.h"


ServComACK::ServComACK()
{
	size = 1;
	communicateBuffer = new char;
	communicateBuffer[0] = 0x01;
}


ServComACK::~ServComACK()
{
	delete communicateBuffer;
}
