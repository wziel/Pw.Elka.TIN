#pragma once
#include "Communicate.h"
#include <random>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

//Server communicate - sending salt needed for hashing a password
class ServComAUTH :
	public Communicate
{
public:
	ServComAUTH();
	~ServComAUTH();
	//returns salt
	string getSalt();

private:
	//generated salt
	string salt;
};

