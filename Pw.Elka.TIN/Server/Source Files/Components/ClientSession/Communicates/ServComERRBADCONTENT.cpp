#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRBADCONTENT.h"


ServComERRBADCONTENT::ServComERRBADCONTENT()
{
	size = 1;
	communicateBuffer = new char;
	communicateBuffer[0] = 0x13;
}


ServComERRBADCONTENT::~ServComERRBADCONTENT()
{
	delete communicateBuffer;
}
