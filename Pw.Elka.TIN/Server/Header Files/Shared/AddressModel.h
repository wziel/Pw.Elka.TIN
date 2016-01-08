#ifndef ADDRESS_MODEL
#define ADDRESS_MODEL

#include <string>

using namespace std;

class AddressModel
{
public:
	AddressModel() {}
	AddressModel(int id,  string value, string name ) : id(id), value(value), name(name) {}
	~AddressModel() {}

	int id;
	string value;
	string name;
};

#endif