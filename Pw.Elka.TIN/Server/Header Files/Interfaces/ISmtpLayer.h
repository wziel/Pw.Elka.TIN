#ifndef I_SMTP_LAYER
#define I_SMTP_LAYER

class MessagesQueue;

class ISmtpLayer
{
public:
	virtual ~ISmtpLayer() {};
	virtual void Start() = 0;
};

#endif