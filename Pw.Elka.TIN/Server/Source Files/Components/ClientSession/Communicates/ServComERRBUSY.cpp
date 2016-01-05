#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRBUSY.h"



ServComERRBUSY::ServComERRBUSY()
{
	size = 1;
	communicateBuffer = new unsigned char;
	communicateBuffer[0] = _SERVCOMERRBUSY;
}


ServComERRBUSY::~ServComERRBUSY()
{
	delete communicateBuffer;
}
