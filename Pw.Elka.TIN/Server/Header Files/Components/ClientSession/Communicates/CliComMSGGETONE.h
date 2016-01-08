#pragma once
#include "Communicate.h"
//Client communicate - request getting one message scheme
class CliComMSGGETONE :
	public Communicate
{
public:
	CliComMSGGETONE(unsigned char* communicateBuffer);
	~CliComMSGGETONE();
	int getMessageId();
private:
	int messageId;
};

