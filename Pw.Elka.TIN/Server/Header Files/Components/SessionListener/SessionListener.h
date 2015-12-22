#ifndef SESSION_LISTENER
#define SESSION_LISTENER

#include "../../Interfaces/ISessionListener.h"
#include "../../Interfaces/IClientCreator.h"
#include <windows.h>
#include <sys/types.h>
#include <winsock.h>
#include <WinSock2.h>
#include <stdlib.h>

class SessionListener :
	public ISessionListener
{
public:
	SessionListener();
	~SessionListener();
	void Start();
	void End();
	void Initialize(IClientCreator &clientCreator);
private:
	IClientCreator *clientCreator;

	int portToListen;	// w konstruktorze/inicie?
	int socketDescriptor;
	int newClientSocketDescriptor;
	int newClientAddressLenght;
	struct sockaddr_in addressStruct;
	struct sockaddr_in newClientAddressStruct;

	WSAEVENT wsaEvents[2];
	int eventSignaled;
};

#endif