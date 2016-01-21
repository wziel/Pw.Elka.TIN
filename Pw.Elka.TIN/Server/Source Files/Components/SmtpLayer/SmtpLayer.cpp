#include "../../../Header Files/Components/SmtpLayer/SmtpLayer.h"
#include <iostream>

class MessagesQueue;

SmtpLayer::SmtpLayer(MessagesQueue* q)
{
	this->queue = q;
}

SmtpLayer::~SmtpLayer()
{
	delete  this->mail;
}

void SmtpLayer::Start()
{
	SmtpMessage smtpMessage ;
	do
	{
		smtpMessage = queue->Pop();
		try
		{

			this->mail = new CSmtp();
			// setting unchangeable serwer details
			mail->SetSMTPServer( Configuration::getConfiguration().getServerSmtpName.c_str() , Configuration::getConfiguration().getPortSmtp);
			mail->SetLogin(Configuration::getConfiguration().getEncryptedSmtpLogin.c_str());
			mail->SetPassword(Configuration::getConfiguration().getEncryptedSmtpPassword.c_str());
			mail->SetSenderMail(Configuration::getConfiguration().getSmtpLogin.c_str());
			mail->SetReplyTo(Configuration::getConfiguration().getSmtpLogin.c_str());
			if (smtpMessage.isQuitMessage)
			{
				return;
			}
			else
			{
				mail->SetSenderName(strcpy((char*)malloc(smtpMessage.sender.length() + 1), smtpMessage.sender.c_str()));

				mail->SetSubject(strcpy((char*)malloc(smtpMessage.title.length() + 1), smtpMessage.title.c_str()));

				while (!smtpMessage.addresses.empty())
				{
					mail->AddRecipient(strcpy((char*)malloc(smtpMessage.addresses.back().length() + 1), smtpMessage.addresses.back().c_str()));
					smtpMessage.addresses.pop_back();
				}
				mail->SetXPriority(XPRIORITY_NORMAL);
				mail->SetXMailer("The Bat! (v3.02) Professional");
				mail->AddMsgLine(strcpy((char*)malloc(smtpMessage.message.length() + 1), smtpMessage.message.c_str()));
				mail->Send();
			}
		}
		catch (ECSmtp e)
		{
			cout << "Error: " << e.GetErrorText().c_str() << ".\n";
		}
		delete this->mail;

	} while (1);
}