#ifndef I_SESSION_LISTENER
#define I_SESSION_LISTENER

class IClientCreator;

class ISessionListener
{
public:
	virtual ~ISessionListener() = 0;
	virtual void StartAsync() = 0;
	virtual void End() = 0;
	virtual void Initialize(IClientCreator &clientCreator) = 0;
};

#endif