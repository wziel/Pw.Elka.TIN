#ifndef SMTP_MESSAGE
#define SMTP_MESSAGE

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class SmtpMessage
{
public:
	SmtpMessage(string sen, string mess, vector<string>& adr) :
		sender(sen), message(mess), addresses(adr) {}
	SmtpMessage(string sen, string mess, string tit , vector<string> &adr) :
		sender(sen), message(mess),  title(tit) , addresses(adr) {}
	SmtpMessage(bool isQuitMessage, vector<string>& add) : isQuitMessage(isQuitMessage), addresses(add) {}
	SmtpMessage(vector<string>& add): addresses(add) {}
	SmtpMessage& operator=( const SmtpMessage& mess) {
	
			this->addresses = mess.addresses;
			this->sender = mess.sender;
			this->title = mess.title;
			this->message = mess.message;
		 
		 return *this;
	}
	~SmtpMessage() {}
	string sender;
	string title;
	string message;
	vector<string> addresses;
	bool isQuitMessage;
};

#endif