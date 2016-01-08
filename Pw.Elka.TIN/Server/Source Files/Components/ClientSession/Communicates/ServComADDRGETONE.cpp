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
														
	//communicateBuffer[1] = 4 & 0xFF;	//address id size
	//communicateBuffer[2] = (4 >> 8) & 0xFF;
	//communicateBuffer[3] = (addressId)& 0xFF;
	//communicateBuffer[4] = (addressId >> 8) & 0xFF;
	//communicateBuffer[5] = (addressId >> 16) & 0xFF;
	//communicateBuffer[6] = (addressId >> 24) & 0xFF;

	//int size = 1 + 2 + 5 + 2 + 4;
	//communicateBuffer = new unsigned char[size];
	//communicateBuffer[0] = 8;
	//unsigned char* myBuffer = communicateBuffer + 1;
	//myBuffer = storeShort(myBuffer, usernameSize);
	//myBuffer = storeString(myBuffer, username);
	//myBuffer = storeShort(myBuffer, passwordSize);
	//myBuffer = storeInt(myBuffer, password);
}


ServComADDRGETONE::~ServComADDRGETONE()
{
}
