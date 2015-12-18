#ifndef I_SMTP_LAYER
#define I_SMTP_LAYER

class MessagesQueue;

class ISmtpLayer
{
public:
	virtual void StartAsync() = 0;
	virtual void Initialize(MessagesQueue &queue) = 0;
};

#endif