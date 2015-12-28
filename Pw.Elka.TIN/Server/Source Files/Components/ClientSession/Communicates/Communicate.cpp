#include "../../../../Header Files/Components/ClientSession/Communicates/Communicate.h"



unsigned char Communicate::getCode()
{
	return communicateBuffer[0];
}

Communicate::Communicate()
{
}

Communicate::Communicate(char* communicateBuffer)
{
	this->communicateBuffer = communicateBuffer;
}

Communicate::~Communicate()
{
}

char* Communicate::getCommunicate()
{
	return communicateBuffer;
}

int Communicate::getSize()
{
	return size;
}