#ifndef GROUP_MODEL
#define GROUP_MODEL

#include <string>
#include <vector>
#include "AddressModel.h"

using namespace std;

/// Klasa reprezentujaca strukturę grupy.
class GroupModel
{
public:
	/// Konstruktor bezargumentowy
	GroupModel() {}
	/// Konstruktor przypisujący wszystkie dane grupy
	/// id - id grupy
	/// name - nazwa grupy
	/// addresses - lista adresów należących do tej grupy
	GroupModel(int id, string name, vector<AddressModel> addresses) : id(id), name(name), addresses(addresses) {}
	/// Konstruktor pomijający przypisanie adresów (w celu wypisania samych nazw grup)
	/// id - id grupy
	/// name - nazwa grupy
	GroupModel(int id, string name) : id(id), name(name) {}
	/// Destruktor
	~GroupModel() {}

	int id;
	string name;
	vector<AddressModel> addresses;
};

#endif
