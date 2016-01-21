#include "../../../Header Files/Components/SessionListener/SessionListener.h"
#include <iostream>

SessionListener::SessionListener(IClientCreator &clientCreator)
{
	this->clientCreator = &clientCreator;
	this->portToListen = Configuration::getConfiguration().getPortToListen();
	wsaEvents[0] = WSACreateEvent();
	wsaEvents[1] = WSACreateEvent();
}

SessionListener::~SessionListener()
{
	WSACloseEvent(wsaEvents[0]);
	WSACloseEvent(wsaEvents[1]);
}

void SessionListener::Start()
{
	try
	{
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;

		wVersionRequested = MAKEWORD(2, 2);

		if (err = WSAStartup(wVersionRequested, &wsaData) != 0)
			throw "WSAStartup error";

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
			eventSignaled = WSAWaitForMultipleEvents(2, wsaEvents, FALSE, WSA_INFINITE, FALSE);
			if (eventSignaled == 0)
			{
				newClientAddressLenght = sizeof(sockaddr_in);
				if ((newClientSocketDescriptor = accept(socketDescriptor, (struct sockaddr *) &newClientAddressStruct, &newClientAddressLenght)) < 0)
				{
					int error = WSAGetLastError();
					throw "Error while accept()";
				}
				else
					clientCreator->CreateClientAsync(newClientSocketDescriptor, newClientAddressStruct, newClientAddressLenght);
				WSAResetEvent(wsaEvents[0]);
			}
			else if (eventSignaled == 1)	// konczymy dzialanie listenera
				break;
			else
				throw "Error in WSAWaitForMultipleEvents";
		}
		if (closesocket(socketDescriptor) != 0)
		{
			int error = WSAGetLastError();
			throw "Error while closesocket()";
		}
	}
	catch (char const* tekst)
	{
		std::cout << tekst << std::endl;
		exit(1);
	}
}

void SessionListener::End()
{
	try
	{
		BOOL ifSucceed;
		if (ifSucceed = WSASetEvent(wsaEvents[1]) == FALSE)
			throw "Blad przy SetEvent!";
	}
	catch (char const* tekst)
	{
		std::cout << tekst << std::endl;
		return;
	}
}
