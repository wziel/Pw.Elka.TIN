#ifndef I_SESSION_LISTENER
#define I_SESSION_LISTENER

class IClientCreator;

class ISessionListener
{
public:
	virtual void StartAsync() = 0;
	virtual void End() = 0;
	virtual void Initialize(IClientCreator &clientCreator) = 0;
};

#endif