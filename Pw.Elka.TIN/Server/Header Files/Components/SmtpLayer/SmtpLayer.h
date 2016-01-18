#ifndef SMTP_LAYER
#define SMTP_LAYER

#include "../../Interfaces/ISmtpLayer.h"
#include "../../Components/SmtpLayer/CSmtp.h"
#include "../../Shared/SmtpMessage.h"
#include "../../Shared/MessagesQueue.h"
/// Klasa reprezentujaca warstwê logikê ³acznosæi klienta smtp z serwerem smtp
class SmtpLayer :
	public ISmtpLayer
{
public:
	/// Konstruktor bezargumentowy
	SmtpLayer(MessagesQueue *queue);
	/// destruktor
	~SmtpLayer();

	///ISmtpLayer
	/// funkjca rozpoczynajaca w¹tek SmtpLayer
	void Start();
private:
	CSmtp* mail;
	MessagesQueue *queue;
};
#endif

