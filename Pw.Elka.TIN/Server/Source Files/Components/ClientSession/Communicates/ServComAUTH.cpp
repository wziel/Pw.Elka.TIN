
#include "../../../../Header Files/Components/ClientSession/Communicates/ServComAUTH.h"


ServComAUTH::ServComAUTH()
{
	srand((unsigned int)time(0));

	//creating communicate
	size = 7;	
	communicateBuffer = new char[7];
	communicateBuffer[0]=0x01;			//communicate code
	communicateBuffer[1]=  (4)& 0xFF;	//salt size
	communicateBuffer[2] = (4 >> 8) & 0xFF;
	communicateBuffer[3] = ((rand() % 89) + 33);
	communicateBuffer[4] = ((rand() % 89) + 33);
	communicateBuffer[5] = ((rand() % 89) + 33);
	communicateBuffer[6] = ((rand() % 89) + 33);

	salt.assign(communicateBuffer[3], 4);
		
}


ServComAUTH::~ServComAUTH()
{
	delete communicateBuffer;
}

string ServComAUTH::getSalt()
{
	return salt;
}

