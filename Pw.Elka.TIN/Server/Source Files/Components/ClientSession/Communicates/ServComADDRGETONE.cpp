#include "../../../../Header Files/Components/ClientSession/Communicates/ServComADDRGETONE.h"



ServComADDRGETONE::ServComADDRGETONE(int addressId)
{
	//throw "Class unimplemented";
	
	//creating communicate 
	size = 7;
	communicateBuffer = new unsigned char[7];
	unsigned char* myBuffer = communicateBuffer + 1;
	communicateBuffer[0] = _SERVCOMADDRGETONE;			//communicate code
	myBuffer = storeShort(myBuffer, 4);
	myBuffer = storeInt(myBuffer, addressId);
}


ServComADDRGETONE::~ServComADDRGETONE()
{
}
