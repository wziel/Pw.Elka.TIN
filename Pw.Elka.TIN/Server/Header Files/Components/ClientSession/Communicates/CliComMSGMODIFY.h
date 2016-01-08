#pragma once
#include "Communicate.h"
//Client communicate - request modyfying a message scheme
class CliComMSGMODIFY :
	public Communicate
{
public:
	CliComMSGMODIFY(unsigned char* communicateBuffer);
	~CliComMSGMODIFY();
	int getMsgId();
	string getMsgContent();
	string getMsgTitle();
private:
	int msgId;
	string msgContent;
	string msgTitle;
};

