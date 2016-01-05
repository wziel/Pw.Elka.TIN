#include "../../../../Header Files/Components/ClientSession/Communicates/Communicate.h"



unsigned char Communicate::getCode()
{
	return communicateBuffer[0];
}

Communicate::Communicate()
{
}

Communicate::Communicate(unsigned char* communicateBuffer)
{
	this->communicateBuffer = communicateBuffer;
}

Communicate::~Communicate()
{
}

unsigned char* Communicate::getCommunicate()
{
	return communicateBuffer;
}

int Communicate::getSize()
{
	return size;
}