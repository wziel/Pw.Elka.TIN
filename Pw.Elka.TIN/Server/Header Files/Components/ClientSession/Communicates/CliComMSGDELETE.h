#pragma once
#include "Communicate.h"
//Client communicate - request deleting a message scheme
class CliComMSGDELETE :
	public Communicate
{
public:
	CliComMSGDELETE(unsigned char* communicateBuffer);
	~CliComMSGDELETE();
	int getMsgId();
private:
	int msgId;
};

