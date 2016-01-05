#pragma once
#include "Communicate.h"
//Cilent communicate - sending data for authorization
using namespace std;

class CliComAUTH :
	public Communicate
{
public:
	CliComAUTH();
	CliComAUTH(unsigned char* communicateBuffer);
	~CliComAUTH();
	string getUsername();
	int getpasswHashAuth();

private:
	//client's username
	string username;
	//password hash (hashed using salt)
	int passwHashAuth;
	// username length
	short int usernameLength;
};

