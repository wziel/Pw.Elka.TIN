#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRBADREQ.h"

ServComERRBADREQ::ServComERRBADREQ()
{
	size = 1;
	communicateBuffer = new unsigned char;
	communicateBuffer[0] = _SERVCOMERRBADREQ;
}


ServComERRBADREQ::~ServComERRBADREQ()
{
	delete communicateBuffer;
}
