#pragma once
#include "../../Interfaces/ILayer.h"
#include "../../Interfaces/ITcpLayerManager.h"

#include <WinSock2.h>
//#include <windows.h>
//#include <sys/types.h>
//#include <winsock.h>


class TcpLayer :
	public ILayer, public ITcpLayerManager
{
public:
	TcpLayer(int socketfd);
	~TcpLayer();
//ITcpLayerManager intereface
	int End();
//ILayer interface
	void Send(unsigned char* buffer, int size);
	void Receive(unsigned char* &buffer, int &size);

private:
//Communication socket descriptor
	int socketFD;
//Array of network events
	WSAEVENT WSAEventArray[2];
//Helper variable - result of function call
	int iResult;
//Signalled event
	int signalledEvent; 
//Buffer for receiving and sending data (excluding header)
	unsigned char* myBuffer;
//Size of buffer for data
	int mySize; 
//Size of buffer for data (byte form)
	unsigned char mySizeBuffer[2];

};

