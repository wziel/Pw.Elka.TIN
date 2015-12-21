#ifndef I_CLIENT_CREATOR
#define I_CLIENT_CREATOR

class IClientCreator
{
public:
	virtual ~IClientCreator() = 0;
	virtual void CreateClientAsync(int socketfd, struct sockaddr_in newClientAddressStruct, int newClientAddressLenght) = 0;
};

#endif