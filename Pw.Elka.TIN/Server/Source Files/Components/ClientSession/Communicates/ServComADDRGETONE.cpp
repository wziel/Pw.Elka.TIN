#include "../../../../Header Files/Components/ClientSession/Communicates/ServComADDRGETONE.h"



ServComADDRGETONE::ServComADDRGETONE(int addressId)
{
	//throw "Class unimplemented";

	//creating communicate
	size = 7;
	communicateBuffer = new unsigned char[7];
	communicateBuffer[0] = _SERVCOMADDRGETONE;			//communicate code
	communicateBuffer[1] = 4 & 0xFF;	//address id size
	communicateBuffer[2] = (4 >> 8) & 0xFF;
	communicateBuffer[3] = (addressId)& 0xFF;
	communicateBuffer[4] = (addressId >> 8) & 0xFF;
	communicateBuffer[5] = (addressId >> 16) & 0xFF;
	communicateBuffer[6] = (addressId >> 24) & 0xFF;
}


ServComADDRGETONE::~ServComADDRGETONE()
{
}
