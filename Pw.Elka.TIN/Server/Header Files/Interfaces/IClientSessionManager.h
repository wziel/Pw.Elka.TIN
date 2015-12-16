#ifndef I_CLIENT_SESSION_MANAGER
#define I_CLIENT_SESSION_MANAGER

class ILayer;
class MessagesQueue;
enum SessionState;
class IClientDAL;
class IClientManager;

class IClientSessionManager
{
public:
	virtual bool Initialize(ILayer &bottomLayer, MessagesQueue &queue, SessionState initialState, IClientDAL &DAL, IClientManager &clientManager) = 0;
	virtual bool StartAsync() = 0;
};

#endif