#ifndef I_SMTP_LAYER
#define I_SMTP_LAYER

class MessagesQueue;

class ISmtpLayer
{
public:
	virtual ~ISmtpLayer() {};
	virtual void Start() = 0;
//	virtual void Initialize(MessagesQueue &queue) = 0;
};

#endif