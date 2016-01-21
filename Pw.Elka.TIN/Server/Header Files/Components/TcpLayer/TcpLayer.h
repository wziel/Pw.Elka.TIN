#pragma once
#include "../../Interfaces/ILayer.h"

class TcpLayer :
	public ILayer
{
public:
	TcpLayer(ILayer &bottomLayer);
	~TcpLayer();
//ILayer interface
	///Sends data to client
	void Send(unsigned char* buffer, int size);
	///Receives data from client
	void Receive(unsigned char* &buffer, int &size);

private:
///Buffer for receiving and sending data (excluding header)
	unsigned char* myBuffer;
///Size of buffer for data
	int mySize; 

///Bottom layer
	ILayer *bottomLayer;

///Size of buffer for data (byte form)
unsigned char* mySizeBuffer;


};

