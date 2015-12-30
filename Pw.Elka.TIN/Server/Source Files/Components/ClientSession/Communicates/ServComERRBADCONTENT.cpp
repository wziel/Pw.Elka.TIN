#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRBADCONTENT.h"


ServComERRBADCONTENT::ServComERRBADCONTENT()
{
	size = 1;
	communicateBuffer = new char;
	communicateBuffer[0] = _SERVCOMERRBADCONTENT;
}


ServComERRBADCONTENT::~ServComERRBADCONTENT()
{
	delete communicateBuffer;
}
