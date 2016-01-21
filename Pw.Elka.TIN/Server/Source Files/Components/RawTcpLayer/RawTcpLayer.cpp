#include "../../../Header Files/Components/RawTcpLayer/RawTcpLayer.h"
#include <iostream>
using namespace std;

RawTcpLayer::RawTcpLayer(int socketfd)
	: socketFD(socketfd)
{
	WSAEventArray[0] = WSACreateEvent();	//event signalling end of client session
	if (WSAEventArray[0] == WSA_INVALID_EVENT)
		throw "WSA error";
	
	WSAEventArray[1] = WSACreateEvent();	//network event - read
	if (WSAEventArray[1] == WSA_INVALID_EVENT)
		throw "WSA error";
	
	iResult = WSAEventSelect(socketFD, WSAEventArray[1],  FD_READ | FD_CLOSE);	//associate event with a socket
	if (iResult != 0)
		throw "WSA error";

	u_long iMode = 1;

	iResult = ioctlsocket(socketFD, FIONBIO,  &iMode);
	if (iResult != NO_ERROR)
		throw "Network error";
}

int RawTcpLayer::End()
{
	if (WSASetEvent(WSAEventArray[0]) == TRUE)	//successfully signal an ending event
		return 0;

	else
		throw "WSA error";
}

void RawTcpLayer::Send(unsigned char* buffer, int size)	//send data to client
{
	//Create a buffer to send 
	mySize = size;
	myBuffer = new unsigned char[mySize];

	for (int i = 0; i < mySize; ++i)
		myBuffer[i] = buffer[i];

	iResult = send(socketFD, (char*)myBuffer, mySize, NULL);	//send message
	if (iResult == SOCKET_ERROR)
		throw "Network error";																			
}

void RawTcpLayer::Receive(unsigned char* &buffer, int &size)	//receive data from client
{
	int receivedBytes = 0;
	mySize = size;
	buffer = new unsigned char[mySize];
	
	do
	{

	iResult = recv(socketFD, (char*)(buffer + receivedBytes), mySize - receivedBytes, NULL);
	if (iResult != SOCKET_ERROR)
	{
		receivedBytes += iResult;
	}
	if (iResult == SOCKET_ERROR&& WSAGetLastError() == WSAEWOULDBLOCK)
	{
		WSAResetEvent(WSAEventArray[1]);
		signalledEvent = WSAWaitForMultipleEvents(2, WSAEventArray, FALSE, WSA_INFINITE, FALSE);	//wait for events - receive a message or end TcpLayer
		if (signalledEvent == WSA_WAIT_FAILED)
			throw "WSA error";

		if ((signalledEvent - WSA_WAIT_EVENT_0) == 0) // end of TcpLayer
			throw "Client ended";

		else if ((signalledEvent - WSA_WAIT_EVENT_0) == 1) //receive a message or client distonnected
		{
			WSAEnumNetworkEvents(socketFD, WSAEventArray[1], &NetworkEvents);
			if (NetworkEvents.lNetworkEvents & FD_READ)
			{
				WSAResetEvent(WSAEventArray[1]);
			}
			else if (NetworkEvents.lNetworkEvents & FD_CLOSE)
				throw "Client ended externally";
			else throw "Network error";

		}
	}
	else if (iResult == SOCKET_ERROR)
		throw "Network error";
	} while (receivedBytes < size);
}

RawTcpLayer::~RawTcpLayer()
{
	WSACloseEvent(WSAEventArray[0]);
	WSACloseEvent(WSAEventArray[1]);
	closesocket(socketFD);
		
}
