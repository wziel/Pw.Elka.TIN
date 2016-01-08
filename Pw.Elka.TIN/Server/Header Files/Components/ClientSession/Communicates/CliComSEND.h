#pragma once
#include "Communicate.h"
#include <vector>

//Client communicate - request sending a message
class CliComSEND :
	public Communicate
{
public:
	CliComSEND(unsigned char* communicateBuffer);
	~CliComSEND();
	int getGrpId();
	int getMsgId();
	vector<string> getFields();
private:
	vector<string> fields;
	int grpId;
	int msgId;
};

