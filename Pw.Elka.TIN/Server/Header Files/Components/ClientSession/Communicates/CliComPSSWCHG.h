#pragma once
#include "Communicate.h"
//Client communicate - request password change
class CliComPSSWCHG :
	public Communicate
{
public:
	CliComPSSWCHG(unsigned char* communicateBuffer);
	~CliComPSSWCHG();
	string getPasswHash();
	string getNewPasswHash();
private:
	string passwHash;
	string newPasswHash;
};

