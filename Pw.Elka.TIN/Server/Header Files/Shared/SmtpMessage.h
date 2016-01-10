#ifndef SMTP_MESSAGE
#define SMTP_MESSAGE

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class SmtpMessage
{
public:
	SmtpMessage(string sender, string message, vector<string>& adr) :
		sender(sender), message(message), addresses(adr) {

	}
	SmtpMessage(string sender, string message, vector<string> &adr, string title) :
		sender(sender), message(message), addresses(adr), title(title) {
	
	}
	SmtpMessage(bool isQuitMessage, vector<string>& add) : isQuitMessage(isQuitMessage), addresses(add) {
	 
	
	}
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