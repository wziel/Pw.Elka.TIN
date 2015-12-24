//@todo - implement reading action (receive)
//@todo - implement send function
//@todo - constructors instead of initialization
//@todo - destructor 

#include "../../../Header Files/Components/TcpLayer/TcpLayer.h"

bool TcpLayer :: Initialize(int socketfd)
{
	this->socketFD = socketfd;
	WSAEventArray[0] = WSACreateEvent();	//event signalling end of client session
		if (WSAEventArray[0] == WSA_INVALID_EVENT)
		{
			throw "WSACreateEvent() error - WSAEventArray[0]";
		}

	WSAEventArray[1] = WSACreateEvent();	//network event - read
		if (WSAEventArray[1] == WSA_INVALID_EVENT)
		{
			throw "WSACreateEvent() error - WSAEventArray[1]";
		}
	iResult = WSAEventSelect(socketFD, WSAEventArray[1], FD_READ);	//associate event with a socket
		if (iResult != 0)
		{
			throw "WSAEventSelect() error";
		}
	return true;
}

int TcpLayer :: End()
{
	if(WSASetEvent(WSAEventArray[1]) == TRUE)
	{
		return 0;
	}
		
	else
	{
		return -1;
	}
}

void TcpLayer :: Send(char* buffer, int size)
{

}

void TcpLayer :: Receive(char* buffer, int size)
{

	signalledEvent = WSAWaitForMultipleEvents(2, WSAEventArray, FALSE, WSA_INFINITE, FALSE);
	if (signalledEvent == WSA_WAIT_FAILED)
	{
		throw "WSAWaitForMultipleEvents() error";
	}

	if ((signalledEvent - WSA_WAIT_EVENT_0 ) == 0)
	{
		return;
	}
	
	else if ((signalledEvent - WSA_WAIT_EVENT_0) == 1)
	{	
		mySize = size + 2;
		myBuffer = new char[mySize];

		iResult = recv(socketFD, myBuffer, mySize, NULL );
		if (iResult == SOCKET_ERROR)
		{
			throw "Recv() error";
		}

		for (int i = 2; i < mySize; ++i)
		{
			buffer[i - 2] = myBuffer[i];
		}

		for (int i = 0; i < mySize; ++i)
		{
			delete myBuffer[i];
		}

		delete myBuffer;
		WSAResetEvent(WSAEventArray[1]);
	}

}


TcpLayer::TcpLayer()
{
}


TcpLayer::~TcpLayer()
{
	WSACloseEvent(WSAEventArray[0]);
	WSACloseEvent(WSAEventArray[1]);
}
