#include "../../../Header Files/Components/Cipher/Cipher.h"
#include <iostream>

Cipher::~Cipher()
{
}

Cipher::Cipher(ILayer &bottomLayer)
{
	this->bottomLayer = &bottomLayer;
}

void Cipher::Send(unsigned char *buffer, int size)
{
	int mySize = size + 3;
	unsigned char *myBuffer = new unsigned char[mySize];
	myBuffer[0] = BYTE (0x00);
	myBuffer[1] = (size) & 0xFF;
	myBuffer[2] = (size >> 8) & 0xFF;
	for (int i = 0; i < size; i++)
		myBuffer[i + 3] = buffer[i] ^ keyCode[i % 6];
	bottomLayer->Send(myBuffer, mySize);
	delete myBuffer;
}

void Cipher::Receive(unsigned char* &buffer, int &size)
{
	int mySize;
	unsigned char *myBuffer=NULL;
	bottomLayer->Receive(myBuffer, mySize);
	buffer = new unsigned char[mySize - 3];
	size = mySize - 3;
	if (myBuffer[0] == 0x00)
	{
		for (int i = 0; i < size; i++)
			buffer[i] = myBuffer[i + 3] ^ keyCode[i % 6];
		delete myBuffer;
	}
	else
		throw "Selected encryption method is not supported";
}
