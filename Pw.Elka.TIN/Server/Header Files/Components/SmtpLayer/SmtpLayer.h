#ifndef SMTP_LAYER
#define SMTP_LAYER

#include "../../Interfaces/ISmtpLayer.h"
#include "../../Components/SmtpLayer/CSmtp.h"
class SmtpLayer :
	public ISmtpLayer
{
public:
	SmtpLayer(MessagesQueue &queue);
	~SmtpLayer();

	//ISmtpLayer
	void Start();
private:
	CSmtp mail;
};
#endif

