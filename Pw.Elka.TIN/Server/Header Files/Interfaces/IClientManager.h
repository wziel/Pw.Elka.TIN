#ifndef I_CLIENT_MANAGER
#define I_CLIENT_MANAGER

#include<string>

class IClientSessionManager;

class IClientManager
{
public:
	virtual ~IClientManager() { };
	virtual void RegisterClientEnded(IClientSessionManager &clientSessionManager) = 0;
	virtual bool DoesSessionExistForClient(std::string loginname) = 0;
};

#endif