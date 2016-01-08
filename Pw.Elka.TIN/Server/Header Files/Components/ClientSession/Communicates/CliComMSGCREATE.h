#pragma once
#include "Communicate.h"
//Client communicate - request creating a message scheme
class CliComMSGCREATE :
	public Communicate
{
public:
	CliComMSGCREATE(unsigned char* communicateBuffer);
	~CliComMSGCREATE();
	string getMsgContent();
	string getMsgTitle();
private:
	string msgContent;
	string msgTitle;
};

