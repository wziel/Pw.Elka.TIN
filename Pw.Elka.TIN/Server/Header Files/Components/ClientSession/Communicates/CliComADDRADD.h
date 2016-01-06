#pragma once
#include "Communicate.h"
#include <string>
using namespace std;
//Client communicate - request adding an address
class CliComADDRADD :
	public Communicate
{
public:
	CliComADDRADD();
	CliComADDRADD(unsigned char* communicateBuffer);
	~CliComADDRADD();
	string getAddressValue();
	short int getAddressValueSize();
	string getAddressName();
	short int getAddressNameSize();
private:
	//e-mail address value
	string addressValue;
	//e-mail address length
	short int addressValueSize;
	//address owner name
	string addressName;
	//e-mail address length
	short int addressNameSize;
};

