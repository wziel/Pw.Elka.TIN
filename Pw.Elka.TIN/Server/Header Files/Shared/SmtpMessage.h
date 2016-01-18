#ifndef SMTP_MESSAGE
#define SMTP_MESSAGE

#include <string>
#include <vector>
#include <iostream>
using namespace std;
/// Klasa reprezentujaca strukturê wiadomosci e-mail
class SmtpMessage
{
public:
	/// Konstruktor bezargumentowy
	SmtpMessage() {}
	/// Konstruktor przypisuj¹cy wszystkie dane wiadomoœci
	/// sender - nadawca
	/// message - nazwa wiadomsoci uzywana w aplikcaji
	/// title - tytu³  wiadomoœci
	/// content - treœæ wiadomoœæi
	/// addresses - odbiorcy wiadomosci
	/// isQuitMessage - wiadomosæ koñcz¹ca w¹tek SmtpLayer
	SmtpMessage(string sen, string mess, string tit, vector<string> &adr, bool isQuitMessage=false) :
		sender(sen), message(mess),  title(tit), addresses(adr), isQuitMessage(isQuitMessage) {}
	/// Konstruktor tworz¹cy wiadomosc zakoñczenia w¹tku dla SmtpLayer
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