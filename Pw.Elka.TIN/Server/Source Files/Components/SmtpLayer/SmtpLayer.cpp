#include "../../../Header Files/Components/SmtpLayer/SmtpLayer.h"
#include <iostream>

class MessagesQueue;

SmtpLayer::SmtpLayer(MessagesQueue* q)
{
	this->queue = q;

	this->mailError = false;
	vector<string> vector1;
}

SmtpLayer::~SmtpLayer()
{
	delete  this->mail;
	delete  this->smtpMessage;
}

void SmtpLayer::Start()
{
	//TESTING !!!

	//vector<string> vector;
	//string gmail = string("kakacper1@gmail.com");
	//vector.push_back(gmail);
	//vector.push_back("kamil9422@interia.pl");
	//SmtpMessage forTry = SmtpMessage("tu rozsylacz", "No to sie w koncu doigrales!\n Pozdrawiam Kamil", "gra skonczona" , vector );
	//forTry.isQuitMessage = false;
	//queue->Push(forTry);




	do
	{
		*smtpMessage = queue->Pop();
		try
		{

			this->mail = new CSmtp();
			// setting unchangeable serwer details
			mail->SetSMTPServer(SERVER, 587);
			mail->SetLogin(LOGIN);
			mail->SetPassword(PWD);
			mail->SetSenderMail(LOGIN);
			mail->SetReplyTo(LOGIN);
			if (smtpMessage->isQuitMessage)
			{
				return;
			}
			else
			{
				mail->SetSenderName(strcpy((char*)malloc(smtpMessage->sender.length() + 1), smtpMessage->sender.c_str()));

				mail->SetSubject(strcpy((char*)malloc(smtpMessage->title.length() + 1), smtpMessage->title.c_str()));

				while (!smtpMessage->addresses.empty())
				{
					mail->AddRecipient(strcpy((char*)malloc(smtpMessage->addresses.back().length() + 1), smtpMessage->addresses.back().c_str()));
					smtpMessage->addresses.pop_back();
				}
				mail->SetXPriority(XPRIORITY_NORMAL);
				mail->SetXMailer("The Bat! (v3.02) Professional");
				mail->AddMsgLine(strcpy((char*)malloc(smtpMessage->message.length() + 1), smtpMessage->message.c_str()));
				mail->Send();
			}
		}
		catch (ECSmtp e)
		{
			cout << "Error: " << e.GetErrorText().c_str() << ".\n";
			mailError = true;
		}
		delete this->mail;

	} while (1);
}