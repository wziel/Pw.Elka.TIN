#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRSERVUNAV.h"



ServComERRSERVUNAV::ServComERRSERVUNAV()
{
	size = 1;
	communicateBuffer = new char;
	communicateBuffer[0] = 0x16;
}


ServComERRSERVUNAV::~ServComERRSERVUNAV()
{
	delete communicateBuffer;
}
