//@todo - klasy wyj¹tków
#include "../../../Header Files/Components/TcpLayer/TcpLayer.h"

bool TcpLayer :: Initialize(int socketfd, ILayer &upperLayer)
{
	//Creating notification socket
	if (initNotificationSocket = socket(AF_INET, SOCK_STREAM, 0) == -1)
	{
		throw "Socket() error - notificationSocket";
	}

	notificationAddress.sin_family = AF_INET;
	notificationAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	notificationAddress.sin_port = htons(notificationPort);

	if (bind(initNotificationSocket, (sockaddr*)&notificationAddress, sizeof notificationAddress) == -1)
	{
		throw "Bind() error - notificationSocket";
	}

	//@todo - check backlog number
	listen(initNotificationSocket, 5);

	if (notificationSocket = accept(initNotificationSocket, (sockaddr*)0, (int*)0) == -1)
	{
		throw "Accept() error - notificationSocket";
	}

	//Creating communication socket
	if (initCommunicationSocket = socket(AF_INET, SOCK_STREAM, 0) == -1)
	{
		throw "Socket() error - communicationSocket"; 
	}

	communicationAddress.sin_family = AF_INET;
	communicationAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	communicationAddress.sin_port = htons(communicationPort);

	if (bind( initCommunicationSocket,(sockaddr*) &communicationAddress, sizeof communicationAddress)  == -1)
	{
		throw "Bind() error - communicationSocket";
	}

	//@todo - check backlog number
	listen(initCommunicationSocket, 5);

	if(communicationSocket = accept(initCommunicationSocket, (sockaddr*)0, (int*)0) == -1)
	{
		throw "Accept() error - communicationSocket";
	}


	//@todo 
	return true;
}

int TcpLayer :: End()
{
	//@todo

	return 0;
}

void TcpLayer :: Send(char* buffer, int size)
{

}

void TcpLayer :: Receive(char* buffer, int size)
{

}


TcpLayer::TcpLayer()
{
}


TcpLayer::~TcpLayer()
{
}
