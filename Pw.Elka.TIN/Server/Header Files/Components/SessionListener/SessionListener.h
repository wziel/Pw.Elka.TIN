#ifndef SESSION_LISTENER
#define SESSION_LISTENER

#include "../../Interfaces/ISessionListener.h"
#include "../../Interfaces/IClientCreator.h"
#include <WinSock2.h>
//#include <windows.h>
//#include <sys/types.h>
//#include <winsock.h>
#include <stdlib.h>

class SessionListener :
	public ISessionListener
{
public:
	SessionListener(IClientCreator &clientCreator);
	~SessionListener();
	//ISessionListener
	void Start();
	void End();
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