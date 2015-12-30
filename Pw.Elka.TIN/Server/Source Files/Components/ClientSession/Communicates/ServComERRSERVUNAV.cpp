#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRSERVUNAV.h"



ServComERRSERVUNAV::ServComERRSERVUNAV()
{
	size = 1;
	communicateBuffer = new char;
	communicateBuffer[0] = _SERVCOMERRSERVUNAV;
}


ServComERRSERVUNAV::~ServComERRSERVUNAV()
{
	delete communicateBuffer;
}
