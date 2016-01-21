//@todo - constructors instead of initialization

#include "../../../Header Files/Components/TcpLayer/TcpLayer.h"

TcpLayer::TcpLayer(ILayer &bottomLayer)
{
	this->bottomLayer = &bottomLayer;
}



void TcpLayer::Send(unsigned char* buffer, int size)	//send data to client
{
	//Create a buffer to send - header+data
	mySize = size + 2;
	myBuffer = new unsigned char[mySize];
	myBuffer[0] = (size)& 0xFF;
	myBuffer[1] = (size >> 8) & 0xFF;

	for (int i = 2; i < mySize; ++i)
	{
		myBuffer[i] = buffer[i - 2];
	}

	bottomLayer->Send(myBuffer, mySize);

	delete[] myBuffer;
}

void TcpLayer::Receive(unsigned char* &buffer, int &size)	//receive data from client
{
			mySize = (((mySizeBuffer[1]) << 8) | (mySizeBuffer[0]));
			size = mySize;

			buffer = new unsigned char[mySize];

			iResult = recv(socketFD, (char*)buffer, mySize, NULL);

}

TcpLayer::~TcpLayer()
{
}
