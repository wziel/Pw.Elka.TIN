#include "../../../Header Files/Components/SessionListener/SessionListener.h"



SessionListener::SessionListener()
{
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

	if (bind(socketDescriptor, (struct sockaddr*)&addressStruct, sizeof(addressStruct)) != 0)
		throw "Error while binding address with socket";

	if (listen(socketDescriptor, 10) != 0)
		throw "Error while setting socket to listen";

	for (; ;)
	{
		newClientSocketDescriptor = accept(socketDescriptor, (struct sockaddr *) &newClientAddressStruct, &newClientAddressLenght);
		if (newClientSocketDescriptor < 0)
			throw "Error while accept()";
		else
			clientCreator->CreateClientAsync(newClientSocketDescriptor, newClientAddressStruct, newClientAddressLenght);
	}
}