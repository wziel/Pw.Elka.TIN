#include "../../../../Header Files/Components/ClientSession/Communicates/ServComGRPGETALL.h"



ServComGRPGETALL::ServComGRPGETALL(vector <GroupModel> * vect)
{
	size = 1 + 2 + 2;
	for (unsigned int i = 0; i < vect->size(); ++i)
	{
		size = size + 2 + 4 + 2 + (*vect)[i].name.length() ;
	}

	communicateBuffer = new unsigned char[size];
	unsigned char* myBuffer = communicateBuffer + 1;
	communicateBuffer[0] = _SERVCOMGRPGETALL;			//communicate code

	myBuffer = storeShort(myBuffer, (short)(vect->size()));

	for (unsigned int i = 0; i < vect->size(); ++i)
	{
		myBuffer = storeShort(myBuffer, 4);
		myBuffer = storeInt(myBuffer, (*vect)[i].id);
	}
	myBuffer = storeShort(myBuffer, (short)(vect->size()));

	for (unsigned int i = 0; i < vect->size(); ++i)
	{
		myBuffer = storeShort(myBuffer, (short)((*vect)[i].name.length()));
		myBuffer = storeString(myBuffer, (*vect)[i].name);
	}
}


ServComGRPGETALL::~ServComGRPGETALL()
{
}
