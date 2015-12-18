#ifndef SMTP_MESSAGE
#define SMTP_MESSAGE

#include <string>
#include <vector>

using namespace std;

class SmtpMessage
{
public:
	SmtpMessage(string sender, string message, vector<string> adresses) :
		sender(sender), message(message), addresses(addresses) {}
	SmtpMessage(bool isQuitMessage) : isQuitMessage(isQuitMessage) {}
	SmtpMessage() {}
	~SmtpMessage() {}
	string sender;
	string message;
	vector<string> addresses;
	bool isQuitMessage;
};

#endif