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
	string serverName = Configuration::getConfiguration().getServerSmtpName();
	char *cServerName = new char[serverName.length() + 1];
	strcpy(cServerName , serverName.c_str());

	string encryptetSmtpLogin = Configuration::getConfiguration().getEncryptedSmtpLogin();
	char *cEncryptetSmtpLogin = new char[encryptetSmtpLogin.length() + 1];
	strcpy(cEncryptetSmtpLogin, encryptetSmtpLogin.c_str());
	
	string encryptetSmtpPassword = Configuration::getConfiguration().getEncryptedSmtpPassword();
	char *cEncryptetSmtpPassword = new char[encryptetSmtpPassword.length() + 1];
	strcpy(cEncryptetSmtpPassword, encryptetSmtpPassword.c_str());

	string smtpLogin = Configuration::getConfiguration().getSmtpLogin();
	char *cSmtpLogin = new char[smtpLogin.length() + 1];
	strcpy(cSmtpLogin, smtpLogin.c_str());

	unsigned short portSmtp = Configuration::getConfiguration().getPortSmtp();

	SmtpMessage smtpMessage ;
	do
	{
		smtpMessage = queue->Pop();
		try
		{

			this->mail = new CSmtp();
			// setting unchangeable serwer details
			mail->SetSMTPServer( cServerName , portSmtp);
			mail->SetLogin(cEncryptetSmtpLogin);
			mail->SetPassword(cEncryptetSmtpPassword);
			mail->SetSenderMail(cSmtpLogin);
			mail->SetReplyTo(cSmtpLogin);
			if (smtpMessage.isQuitMessage)
			{
				delete[] cServerName;
				delete[] cEncryptetSmtpLogin;
				delete[] cEncryptetSmtpPassword;
				delete[] cSmtpLogin;
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