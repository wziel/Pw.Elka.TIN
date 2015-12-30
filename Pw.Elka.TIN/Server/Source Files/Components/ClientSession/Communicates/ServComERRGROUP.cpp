#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRGROUP.h"


ServComERRGROUP::ServComERRGROUP()
{
	size = 1;
	communicateBuffer = new char;
	communicateBuffer[0] = 0x14;
}


ServComERRGROUP::~ServComERRGROUP()
{
	delete communicateBuffer;
}
