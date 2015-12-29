#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRBADREQ.h"

ServComERRBADREQ::ServComERRBADREQ()
{
	size = 1;
	communicateBuffer = new char;
	communicateBuffer[0] = 0x12;
}


ServComERRBADREQ::~ServComERRBADREQ()
{
	delete communicateBuffer;
}
