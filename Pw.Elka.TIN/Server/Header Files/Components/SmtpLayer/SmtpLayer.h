#ifndef SMTP_LAYER
#define SMTP_LAYER

#include "../../Interfaces/ISmtpLayer.h"
#include "../../Components/SmtpLayer/CSmtp.h"
#include "../../Shared/SmtpMessage.h"
#include "../../Shared/MessagesQueue.h"

class SmtpLayer :
	public ISmtpLayer
{
public:
	SmtpLayer(MessagesQueue *queue);
	~SmtpLayer();

	//ISmtpLayer
	void Start();
private:
	CSmtp* mail;
	MessagesQueue *queue;
	bool mailError;
	SmtpMessage* smtpMessage;
};
#endif

