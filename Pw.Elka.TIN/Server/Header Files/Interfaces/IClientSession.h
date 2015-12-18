#ifndef I_CLIENT_SESSION
#define I_CLIENT_SESSION

class IClientSession
{
public:
	virtual ~IClientSession() = 0;
	virtual void PassData(char* buffer, int size) = 0;
};

#endif