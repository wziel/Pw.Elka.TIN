#include "../../../Header Files/Components/Cipher/Cipher.h"
#include <iostream>



Cipher::Cipher()
{
}


Cipher::~Cipher()
{
}

void Cipher::Initialize(ILayer &bottomLayer)
{
	this->bottomLayer = &bottomLayer;
}

void Cipher::Send(char *buffer, int size)
{
	int mySize = size + 3;
	char *myBuffer = new char[mySize];
	myBuffer[0] = BYTE (0x00);
	myBuffer[1] = (mySize) & 0xFF;
	myBuffer[2] = (mySize >> 8) & 0xFF;
	for (int i = 0; i < size; i++)
		myBuffer[i + 3] = buffer[i] ^ keyCode[i % 6];
	bottomLayer->Send(myBuffer, size + 3);
	delete myBuffer;
}

void Cipher::Receive(char *buffer, int &size)	//znamy juz rozmiar?
{
	int mySize;
	char *myBuffer;
	bottomLayer->Receive(myBuffer, mySize);
	buffer = new char[mySize - 3];
	if (myBuffer[0] == 0x00)
	{
		for (int i = 0; i < size; i++)
			buffer[i] = myBuffer[i + 3] ^ keyCode[i % 6];
		delete myBuffer;
	}
	else
		throw "Not implemented";
}
