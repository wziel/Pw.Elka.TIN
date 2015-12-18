#pragma once
#include "../../Interfaces/ILayer.h"
#include "../../Interfaces/ITcpLayerManager.h"

#include <windows.h>
#include <sys/types.h>
#include <winsock.h>

class TcpLayer :
	public ILayer, public ITcpLayerManager
{
public:
	TcpLayer();
	~TcpLayer();
//ITcpLayerManager intereface
	bool Initialize(int socketfd, ILayer &upperLayer);
	int End();
//ILayer interface
	void Send(char* buffer, int size) = 0;
	void Receive(char* buffer, int size) = 0;

private:
//Socket used to communicate with client - descriptor returnet by socket()
	int initCommunicationSocket;
//Socket used for getting notification from Root Manager (information that client session ended) - descriptor returned by socket()
	int initNotificationSocket;
//Communication socket - descriptor returned by accept()
	int communicationSocket;
//Notification socket - descriptor returned by accept()
	int notificationSocket;
//Communication port number
	int communicationPort;
//Notification port number
	int notificationPort;
//Communication address structure
	struct sockaddr_in communicationAddress;
//Notification address structure
	struct sockaddr_in notificationAddress;
//Set of socket descriptors
	fd_set socketsTcpLayer;



};

