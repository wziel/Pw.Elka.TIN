//@todo - constructors instead of initialization

#include "../../../Header Files/Components/RawTcpLayer/RawTcpLayer.h"

RawTcpLayer::RawTcpLayer(int socketfd)
	: socketFD(socketfd)
{
	WSAEventArray[0] = WSACreateEvent();	//event signalling end of client session
	if (WSAEventArray[0] == WSA_INVALID_EVENT)
		throw "WSA error";
	
	WSAEventArray[1] = WSACreateEvent();	//network event - read
	if (WSAEventArray[1] == WSA_INVALID_EVENT)
		throw "WSA error";
	
	iResult = WSAEventSelect(socketFD, WSAEventArray[1], FD_WRITE | FD_READ | FD_CLOSE);	//associate event with a socket
	if (iResult != 0)
		throw "WSA error";
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
	//myBuffer = new unsigned char[mySize];

	//for (int i = 0; i < mySize; ++i)
	//	myBuffer[i] = buffer[i];
	
	signalledEvent = WSAWaitForMultipleEvents(2, WSAEventArray, FALSE, WSA_INFINITE, FALSE);	//wait for events - send a message or end TcpLayer
	if (signalledEvent == WSA_WAIT_FAILED)
		throw "WSA error";
	
	if ((signalledEvent - WSA_WAIT_EVENT_0) == 0) // end of TcpLayer
		throw "Client ended";
	
	else if ((signalledEvent - WSA_WAIT_EVENT_0) == 1) //send a message or client distonnected
	{
		WSAEnumNetworkEvents(socketFD, WSAEventArray[1], &NetworkEvents);
		if (NetworkEvents.lNetworkEvents & FD_WRITE)
		{
			//iResult = send(socketFD, (char*)myBuffer, mySize, NULL);	//send message
			iResult = send(socketFD, (char*)buffer, mySize, NULL);	//send message
			if (iResult == SOCKET_ERROR)
				throw "Network error";
			
			//delete[] myBuffer;
		}
		else if (NetworkEvents.lNetworkEvents & FD_CLOSE)
			throw "Client ended externally";
		else throw "Network error";

		WSAResetEvent(WSAEventArray[1]);
	}																				
}

void RawTcpLayer::Receive(unsigned char* &buffer, int &size)	//receive data from client
{
	int receivedBytes = 0;
	mySize = size;
	buffer = new unsigned char[mySize];

	while (receivedBytes != size)
	{
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
				iResult = recv(socketFD, (char*)(buffer+receivedBytes), mySize-receivedBytes, NULL);
				if (iResult == SOCKET_ERROR)
					throw "Network error";
				
				receivedBytes += iResult;
			}
			else if (NetworkEvents.lNetworkEvents & FD_CLOSE)
				throw "Client ended externally";
			else throw "Network error";

			WSAResetEvent(WSAEventArray[1]);
		}
	}
}

RawTcpLayer::~RawTcpLayer()
{
	WSACloseEvent(WSAEventArray[0]);
	WSACloseEvent(WSAEventArray[1]);
	closesocket(socketFD);
		
}