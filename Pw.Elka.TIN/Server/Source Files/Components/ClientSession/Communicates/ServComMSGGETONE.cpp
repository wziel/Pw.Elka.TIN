#include "../../../../Header Files/Components/ClientSession/Communicates/ServComMSGGETONE.h"


ServComMSGGETONE::ServComMSGGETONE(MessageModel *messageDB)
{
	size = 1 + 2 + 4 + 2 + messageDB->content.length() + 2 + messageDB->title.length();


	communicateBuffer = new unsigned char[size];
	unsigned char* myBuffer = communicateBuffer + 1;
	communicateBuffer[0] = _SERVCOMMSGGETONE;			//communicate code

	myBuffer = storeShort(myBuffer, 4);
	myBuffer = storeInt(myBuffer, messageDB->id);

	myBuffer = storeShort(myBuffer, messageDB->content.length());
	myBuffer = storeString(myBuffer, messageDB->content);

	myBuffer = storeShort(myBuffer, messageDB->title.length());
	myBuffer = storeString(myBuffer, messageDB->title);

}


ServComMSGGETONE::~ServComMSGGETONE()
{
}
