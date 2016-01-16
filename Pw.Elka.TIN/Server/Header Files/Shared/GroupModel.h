#ifndef GROUP_MODEL
#define GROUP_MODEL

#include <string>
#include <vector>
#include "AddressModel.h"

using namespace std;

/// Klasa reprezentujaca strukturê grupy.
class GroupModel
{
public:
	/// Konstruktor bezargumentowy
	GroupModel() {}
	/// Konstruktor przypisuj¹cy wszystkie dane grupy
	/// id - id grupy
	/// name - nazwa grupy
	/// addresses - lista adresów nale¿¹cych do tej grupy
	GroupModel(int id, string name, vector<AddressModel> addresses) : id(id), name(name), addresses(addresses) {}
	/// Konstruktor pomijaj¹cy przypisanie adresów (w celu wypisania samych nazw grup)
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
