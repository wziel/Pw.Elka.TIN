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

unsigned char* Communicate::storeInt(unsigned char* buffer, int val)
{
	buffer[0] = (val)& 0xFF;
	buffer[1] = (val >> 8) & 0xFF;
	buffer[2] = (val >> 16) & 0xFF;
	buffer[3] = (val >> 24) & 0xFF;
	return buffer + 4;
}

unsigned char* Communicate::storeShort(unsigned char* buffer, short val)
{
	buffer[0] = (val)& 0xFF;
	buffer[1] = (val >> 8) & 0xFF;
	return buffer + 2;
}

unsigned char* Communicate::storeString(unsigned char* buffer, string val)
{
	const char* valSplit = val.c_str();
	for (unsigned int i = 0; i < val.length(); ++i)
	{
		buffer[i] = valSplit[i];
	}
	return buffer + val.length();

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