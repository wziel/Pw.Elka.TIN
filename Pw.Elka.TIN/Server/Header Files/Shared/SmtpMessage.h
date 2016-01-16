#ifndef SMTP_MESSAGE
#define SMTP_MESSAGE

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class SmtpMessage
{
public:
	SmtpMessage(string sen, string mess, string tit, vector<string> &adr, bool isQuitMessage=false) :
		sender(sen), message(mess),  title(tit), addresses(adr), isQuitMessage(isQuitMessage) {}
	SmtpMessage(vector<string>& add) : addresses(add) {}
	SmtpMessage(bool isQuitMessage) :
		isQuitMessage(isQuitMessage) {}
	~SmtpMessage() {}
	string sender;
	string title;
	string message;
	vector<string> addresses;
	bool isQuitMessage;
};

#endif