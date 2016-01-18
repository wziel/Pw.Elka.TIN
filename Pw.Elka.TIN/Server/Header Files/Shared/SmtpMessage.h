#ifndef SMTP_MESSAGE
#define SMTP_MESSAGE

#include <string>
#include <vector>
#include <iostream>
using namespace std;
/// Klasa reprezentujaca struktur� wiadomosci e-mail
class SmtpMessage
{
public:
	/// Konstruktor bezargumentowy
	SmtpMessage() {}
	/// Konstruktor przypisuj�cy wszystkie dane wiadomo�ci
	/// sender - nadawca
	/// message - nazwa wiadomsoci uzywana w aplikcaji
	/// title - tytu�  wiadomo�ci
	/// content - tre�� wiadomo��i
	/// addresses - odbiorcy wiadomosci
	/// isQuitMessage - wiadomos� ko�cz�ca w�tek SmtpLayer
	SmtpMessage(string sen, string mess, string tit, vector<string> &adr, bool isQuitMessage=false) :
		sender(sen), message(mess),  title(tit), addresses(adr), isQuitMessage(isQuitMessage) {}
	/// Konstruktor tworz�cy wiadomosc zako�czenia w�tku dla SmtpLayer
	SmtpMessage(bool isQuitMessage) :
		isQuitMessage(isQuitMessage) {}
	/// Destruktor
	~SmtpMessage() {}
	string sender;
	string title;
	string message;
	vector<string> addresses;
	bool isQuitMessage;
};

#endif