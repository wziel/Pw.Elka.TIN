#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRMSG.h"



ServComERRMSG::ServComERRMSG()
{
	size = 1;
	communicateBuffer = new unsigned char;
	communicateBuffer[0] = _SERVCOMERRMSG;
}


ServComERRMSG::~ServComERRMSG()
{
	delete communicateBuffer;
}
