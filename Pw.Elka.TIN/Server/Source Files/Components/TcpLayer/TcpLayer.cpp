//@todo - constructors instead of initialization

#include "../../../Header Files/Components/TcpLayer/TcpLayer.h"

TcpLayer::TcpLayer(ILayer& bottomLayer)
{
	throw "not implemented tcp layer constructor";
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

	iResult = send(socketFD, (char*)myBuffer, mySize, NULL);	//send message
	if (iResult == SOCKET_ERROR)
	{
		throw "Network error";
	}

	delete[] myBuffer;
}

void TcpLayer::Receive(unsigned char* &buffer, int &size)	//receive data from client
{

	signalledEvent = WSAWaitForMultipleEvents(2, WSAEventArray, FALSE, WSA_INFINITE, FALSE);	//wait for events - receive a message or end TcpLayer
	if (signalledEvent == WSA_WAIT_FAILED)
	{
		throw "WSA error";
	}

	if ((signalledEvent - WSA_WAIT_EVENT_0) == 0) // end of TcpLayer
	{
		throw "Client ended";
	}

	else if ((signalledEvent - WSA_WAIT_EVENT_0) == 1) //receive a message or client distonnected
	{
		WSAEnumNetworkEvents(socketFD, WSAEventArray[1], &NetworkEvents);
		if (NetworkEvents.lNetworkEvents & FD_READ)
		{
			iResult = recv(socketFD, (char*)mySizeBuffer, 2, NULL); //reading header (contains data size)
			if (iResult == SOCKET_ERROR)
			{
				throw "Network error";
			}

			mySize = (((mySizeBuffer[1]) << 8) | (mySizeBuffer[0]));
			size = mySize;

			buffer = new unsigned char[mySize];

			iResult = recv(socketFD, (char*)buffer, mySize, NULL);
			if (iResult == SOCKET_ERROR)
			{
				throw "Network error";
			}
		}
		else if (NetworkEvents.lNetworkEvents & FD_CLOSE)
			throw "Client ended externally";
		

		WSAResetEvent(WSAEventArray[1]);
	}
}

TcpLayer::~TcpLayer()
{
	WSACloseEvent(WSAEventArray[0]);
	WSACloseEvent(WSAEventArray[1]);
}
