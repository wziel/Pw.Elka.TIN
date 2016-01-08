#include "../../../../Header Files/Components/ClientSession/Communicates/ServComMSGGETALL.h"

 

ServComMSGGETALL::ServComMSGGETALL(vector <MessageModel> * vect)
{
	size = 1 + 2 + 2;
	for (unsigned int i = 0; i < vect->size(); ++i)
	{
		size = size + 2 + 4 + 2 + (*vect)[i].title.length();
	}

	communicateBuffer = new unsigned char[size];
	unsigned char* myBuffer = communicateBuffer + 1;
	communicateBuffer[0] = _SERVCOMMSGGETALL;			//communicate code

	myBuffer = storeShort(myBuffer, (short)(vect->size()));

	for (unsigned int i = 0; i < vect->size(); ++i)
	{
		myBuffer = storeShort(myBuffer, 4);
		myBuffer = storeInt(myBuffer, (*vect)[i].id);
	}
	myBuffer = storeShort(myBuffer, (short)(vect->size()));

	for (unsigned int i = 0; i < vect->size(); ++i)
	{
		myBuffer = storeShort(myBuffer, (short)((*vect)[i].title.length()));
		myBuffer = storeString(myBuffer, (*vect)[i].title);
	}
}


ServComMSGGETALL::~ServComMSGGETALL()
{
}
