#include "../../../../Header Files/Components/ClientSession/Communicates/Communicate.h"

int Communicate::parseInt(unsigned char** buffer)
{
	int val = 0;
	val = ((*buffer)[3] << 24 | (*buffer)[2] << 16 | (*buffer)[1] << 8 | (*buffer)[0]);
	*buffer = *buffer + 4;
	return val;

}

short int Communicate::parseShort(unsigned char** buffer)
{
	int val = 0;
	val = ((*buffer)[1] << 8 | (*buffer)[0]);
	*buffer = *buffer + 2;
	return val;
}

string Communicate::parseString(unsigned char** buffer)
{
	string mystring;
	int stringlength;
	stringlength = parseShort(buffer);
	mystring.assign((char*)(*buffer), stringlength);
	*buffer = *buffer + stringlength;
	return mystring;
}

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