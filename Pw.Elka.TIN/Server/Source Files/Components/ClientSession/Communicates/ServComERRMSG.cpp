#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRMSG.h"



ServComERRMSG::ServComERRMSG()
{
	size = 1;
	communicateBuffer = new char;
	communicateBuffer[0] = 0x15;
}


ServComERRMSG::~ServComERRMSG()
{
	delete communicateBuffer;
}
