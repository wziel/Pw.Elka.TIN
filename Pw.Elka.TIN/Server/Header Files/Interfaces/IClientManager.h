#ifndef I_CLIENT_MANAGER
#define I_CLIENT_MANAGER

class IClientSessionManager;

class IClientManager
{
public:
	virtual ~IClientManager() = 0;
	virtual void RegisterClientEnded(IClientSessionManager &clientSessionManager, unsigned int clientThreadId) = 0;
};

#endif