#include "../../../../Header Files/Components/ClientSession/Communicates/ServComGRPGETONE.h"

ServComGRPGETONE::ServComGRPGETONE(GroupModel *groupDB)
{
	size = 1 + 2 + 4 + 2 +groupDB->name.length() + 2 + 2;
	for (unsigned int i = 0; i < groupDB->addresses.size(); ++i)
	{
		size = size + 2 + 4 + 2 + groupDB->addresses[i].value.size();
	}
	 
	communicateBuffer = new unsigned char[size];
	unsigned char* myBuffer = communicateBuffer + 1;
	communicateBuffer[0] = _SERVCOMGRPGETONE;			//communicate code

	myBuffer = storeShort(myBuffer, 4);
	myBuffer = storeInt(myBuffer, groupDB->id);

	myBuffer = storeShort(myBuffer, (short)(groupDB->name.length()));
	myBuffer = storeString(myBuffer, groupDB->name);

	myBuffer = storeShort(myBuffer, (short)(groupDB->addresses.size()));

	for (unsigned int i = 0; i < groupDB->addresses.size(); ++i)
	{
		myBuffer = storeShort(myBuffer, 4);
		myBuffer = storeInt(myBuffer, groupDB->addresses[i].id);
	}
	myBuffer = storeShort(myBuffer, (short)(groupDB->addresses.size()));

	for (unsigned int i = 0; i < groupDB->addresses.size(); ++i)
	{
		myBuffer = storeShort(myBuffer, (short)(groupDB->addresses[i].value.size()));
		myBuffer = storeString(myBuffer, groupDB->addresses[i].value);
	}
}


ServComGRPGETONE::~ServComGRPGETONE()
{
}


