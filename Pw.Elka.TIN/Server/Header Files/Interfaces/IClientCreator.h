#ifndef I_CLIENT_CREATOR
#define I_CLIENT_CREATOR

class IClientCreator
{
public:
	virtual ~IClientCreator() = 0;
	virtual void CreateClientAsync(int socketfd) = 0;
};

#endif