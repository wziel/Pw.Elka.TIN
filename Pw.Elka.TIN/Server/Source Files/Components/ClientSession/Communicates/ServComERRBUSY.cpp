#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRBUSY.h"



ServComERRBUSY::ServComERRBUSY()
{
	size = 1;
	communicateBuffer = new char;
	communicateBuffer[0] = 0x10;
}


ServComERRBUSY::~ServComERRBUSY()
{
	delete communicateBuffer;
}
