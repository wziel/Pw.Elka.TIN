#include "../../../Header Files/Components/SmtpLayer/SmtpLayer.h"

#define _CRT_SECURE_NO_WARNINGS

class MessagesQueue;

SmtpLayer::SmtpLayer(MessagesQueue* q)
{
	this->queue = q;
	this->mail = new CSmtp();
	this->mailError = false;
	this->smtpMessage = new SmtpMessage( false ); // delete  it
}

SmtpLayer::~SmtpLayer()
{
	delete  this->mail;
	delete  this->smtpMessage;
}

void SmtpLayer::Start()
{

	try
	{
		// setting unchangeable serwer details
		mail->SetSMTPServer(SERVER, 587);
		mail->SetLogin(LOGIN);
		mail->SetPassword(PWD);
		mail->SetSenderMail(LOGIN);
		mail->SetReplyTo(LOGIN);

		do
		{
			*smtpMessage = queue->Pop();
			if (smtpMessage->isQuitMessage)
			{
				return;
			}
			else
			{

				mail->SetSenderName(strcpy((char*)malloc(smtpMessage->sender.length() + 1), smtpMessage->sender.c_str()));
				mail->SetSubject(strcpy((char*)malloc(smtpMessage->title.length() + 1), smtpMessage->title.c_str()));
				//while
				//mail->AddRecipient(strcpy((char*)malloc(smtpMessage->sender.length() + 1), smtpMessage->sender.c_str()));
				mail->SetXPriority(XPRIORITY_NORMAL);
				mail->SetXMailer("The Bat! (v3.02) Professional");
				mail->AddMsgLine("Hello,");
				//mail.Send();
			}
		} while (1);

	}
	catch (ECSmtp e)
	{
		//std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
	//	int u;
		//std::cin >> u;
		//bError = true;
	//}
	//if (!bError)
	//	std::cout << "Mail was send successfully.\n";
//	int i;
//	std::cin >> i;
//	return 0;
	}
}