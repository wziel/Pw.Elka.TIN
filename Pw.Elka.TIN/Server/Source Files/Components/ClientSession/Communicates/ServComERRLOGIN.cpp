#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRLOGIN.h"


ServComERRLOGIN::ServComERRLOGIN()
{
	size = 1;
	communicateBuffer = new char;
	communicateBuffer[0] = _SERVCOMERRLOGIN;
}


ServComERRLOGIN::~ServComERRLOGIN()
{
	delete communicateBuffer;
}
