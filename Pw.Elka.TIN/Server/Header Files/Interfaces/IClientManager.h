#ifndef I_CLIENT_MANAGER
#define I_CLIENT_MANAGER

class IClientSessionManager;

class IClientManager
{
public:
	virtual void RegisterClientEnded(IClientSessionManager &clientSessionManager) = 0;
};

#endif