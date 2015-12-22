#include "../../../Header Files/Components/SessionListener/SessionListener.h"



SessionListener::SessionListener()
{
	this->portToListen = 7777;
	wsaEvents[0]= WSACreateEvent();
	wsaEvents[1] = WSACreateEvent();
	isEnd = false;
}


SessionListener::~SessionListener()
{
}

void SessionListener::Initialize(IClientCreator &clientCreator)
{
	this->clientCreator = &clientCreator;
}

void SessionListener::Start()
{
	if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw "Error while creating socket";

	addressStruct.sin_family = AF_INET;
	addressStruct.sin_addr.s_addr = htonl(INADDR_ANY);
	addressStruct.sin_port = htons(portToListen);

	if (bind(socketDescriptor, (struct sockaddr *) &addressStruct, sizeof(addressStruct)) != 0)
		throw "Error while binding address with socket";

	if (listen(socketDescriptor, 10) != 0)
		throw "Error while setting socket to listen";

	WSAEventSelect(socketDescriptor, wsaEvents[0], FD_ACCEPT);
	while (true)
	{
		eventSignaled = WSAWaitForMultipleEvents(1, wsaEvents, FALSE, WSA_INFINITE, FALSE);
		if (eventSignaled == 0)
		{
			newClientSocketDescriptor = accept(socketDescriptor, (struct sockaddr *) &newClientAddressStruct, &newClientAddressLenght);
			if (newClientSocketDescriptor < 0)
				throw "Error while accept()";
			else
				clientCreator->CreateClientAsync(newClientSocketDescriptor, newClientAddressStruct, newClientAddressLenght);
		}
		else if (eventSignaled == 1)	// konczymy dzialanie listenera
		{
			break;
		}
	}
	closesocket(socketDescriptor);
}

void SessionListener::End()
{
	WSASetEvent(wsaEvents[1]);
}