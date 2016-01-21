#pragma once
#include "../../Interfaces/ILayer.h"

#include <WinSock2.h>

class TcpLayer :
	public ILayer
{
public:
	TcpLayer(ILayer& bottomLayer);
	~TcpLayer();
//ILayer interface
	///Sends data to client
	void Send(unsigned char* buffer, int size);
	///Receives data from client
	void Receive(unsigned char* &buffer, int &size);

private:
///Communication socket descriptor
	int socketFD;
///Array of network events
	WSAEVENT WSAEventArray[2];
///Network events associated with WSAEventArray[0]
	WSANETWORKEVENTS NetworkEvents;
///Helper variable - result of function call
	int iResult;
///Signalled event
	int signalledEvent; 
///Buffer for receiving and sending data (excluding header)
	unsigned char* myBuffer;
///Size of buffer for data
	int mySize; 
///Size of buffer for data (byte form)
	unsigned char mySizeBuffer[2];



};

