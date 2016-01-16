#ifndef ADDRESS_MODEL
#define ADDRESS_MODEL

#include <string>

using namespace std;

/// Klasa reprezentujaca struktur� adresu.
class AddressModel
{
public:
	/// Konstruktor bezargumentowy
	AddressModel() {}
	/// Konstruktor przypisuj�cy wszystkie dane adresu
	/// id - id adresu
	/// value - warto�� adresu (czyli w�a�ciwy adres)
	/// name - nazwa adresu
	AddressModel(int id,  string value, string name ) : id(id), value(value), name(name) {}
	/// Destruktor
	~AddressModel() {}

	int id;
	string value;
	string name;
};

#endif