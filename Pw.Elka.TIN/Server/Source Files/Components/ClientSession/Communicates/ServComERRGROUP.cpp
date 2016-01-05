#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRGROUP.h"


ServComERRGROUP::ServComERRGROUP()
{
	size = 1;
	communicateBuffer = new unsigned char;
	communicateBuffer[0] = _SERVCOMERRGROUP;
}


ServComERRGROUP::~ServComERRGROUP()
{
	delete communicateBuffer;
}
