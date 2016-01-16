#ifndef ADDRESS_MODEL
#define ADDRESS_MODEL

#include <string>

using namespace std;

/// Klasa reprezentujaca strukturê adresu.
class AddressModel
{
public:
	/// Konstruktor bezargumentowy
	AddressModel() {}
	/// Konstruktor przypisuj¹cy wszystkie dane adresu
	/// id - id adresu
	/// value - wartoœæ adresu (czyli w³aœciwy adres)
	/// name - nazwa adresu
	AddressModel(int id,  string value, string name ) : id(id), value(value), name(name) {}
	/// Destruktor
	~AddressModel() {}

	int id;
	string value;
	string name;
};

#endif