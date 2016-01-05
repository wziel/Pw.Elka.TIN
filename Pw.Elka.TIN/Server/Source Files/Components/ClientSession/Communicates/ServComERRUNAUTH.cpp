#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRUNAUTH.h"

ServComERRUNAUTH::ServComERRUNAUTH()
{
	size = 1;
	communicateBuffer = new unsigned char;
	communicateBuffer[0] = _SERVCOMERRUNAUTH;
}


ServComERRUNAUTH::~ServComERRUNAUTH()
{
	delete communicateBuffer;
}
