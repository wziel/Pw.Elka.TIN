#ifndef I_CLIENT_SESSION_MANAGER
#define I_CLIENT_SESSION_MANAGER

#include <string>

class ILayer;
class MessagesQueue;
enum SessionState;
class IClientDAL;
class IClientManager;

using namespace std;

class IClientSessionManager
{
public:
	virtual ~IClientSessionManager() = 0;
	virtual bool Initialize(ILayer &bottomLayer, MessagesQueue &queue, SessionState initialState, IClientDAL &DAL, IClientManager &clientManager) = 0;
	virtual bool Start() = 0;
	virtual string GetClientName() = 0;
};

#endif