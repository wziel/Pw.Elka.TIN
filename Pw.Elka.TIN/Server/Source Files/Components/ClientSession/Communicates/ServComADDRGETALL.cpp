#include "../../../../Header Files/Components/ClientSession/Communicates/ServComADDRGETALL.h"


ServComADDRGETALL::ServComADDRGETALL(vector<AddressModel>* addrVect)
{
	size = 1 + 2 + 2 + 2;
	for (unsigned int i = 0; i < addrVect->size(); ++i)
	{
		size = size + 2+4 + 2+(*addrVect)[i].value.length() + 2+(*addrVect)[i].name.length();
	}
	
	communicateBuffer = new unsigned char[size];
	unsigned char* myBuffer = communicateBuffer + 1;
	communicateBuffer[0] = _SERVCOMADDRGETALL;			//communicate code
	
	myBuffer = storeShort(myBuffer, (short)(addrVect->size()));
	
	for (unsigned int i = 0; i < addrVect->size(); ++i) 
	{
		myBuffer = storeShort(myBuffer, 4);
		myBuffer = storeInt(myBuffer, (*addrVect)[i].id);
	}
	myBuffer = storeShort(myBuffer, (short)(addrVect->size()));

	for (unsigned int i = 0; i < addrVect->size(); ++i)
	{
		myBuffer = storeShort(myBuffer, (short)((*addrVect)[i].value.length()));
		myBuffer = storeString(myBuffer, (*addrVect)[i].value);
	}
	myBuffer = storeShort(myBuffer, (short)(addrVect->size()));

	for (unsigned int i = 0; i < addrVect->size(); ++i)
	{
		myBuffer = storeShort(myBuffer, (short)((*addrVect)[i].name.length()));
		myBuffer = storeString(myBuffer, (*addrVect)[i].name);
	}

}


ServComADDRGETALL::~ServComADDRGETALL()
{
}
