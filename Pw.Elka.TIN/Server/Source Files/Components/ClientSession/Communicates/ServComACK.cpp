#include "../../../../Header Files/Components/ClientSession/Communicates/ServComACK.h"


ServComACK::ServComACK()
{
	size = 1;
	communicateBuffer = new unsigned char;
	communicateBuffer[0] = _SERVCOMACK;
}


ServComACK::~ServComACK()
{
	delete communicateBuffer;
}
