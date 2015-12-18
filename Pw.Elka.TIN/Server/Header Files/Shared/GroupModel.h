#ifndef GROUP_MODEL
#define GROUP_MODEL

#include <string>
#include <vector>
#include "AddressModel.h"

using namespace std;

class GroupModel
{
public:
	GroupModel() {}
	GroupModel(int id, string name, vector<AddressModel> addresses) : id(id), name(name), addresses(addresses) {}
	~GroupModel() {}

	int id;
	string name;
	vector<AddressModel> addresses;
};

#endif
