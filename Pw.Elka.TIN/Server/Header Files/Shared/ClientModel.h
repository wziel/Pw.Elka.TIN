#ifndef CLIENT_MODEL
#define CLIENT_MODEL

#include <string>

using namespace std;

/// Klasa reprezentujaca strukturê klienta.
class ClientModel
{
public:
	/// Konstruktor bezargumentowy
	ClientModel() {}
	/// Konstruktor przypisuj¹cy wszystkie dane klienta
	/// id - id klienta
	/// login - login klienta
	/// hashOfPassword - hash has³a klienta
	ClientModel(int id, string login, string hashOfPassword) : id(id), login(login), hashOfPassword(hashOfPassword) {}
	/// Destruktor
	~ClientModel() {}

	int id;
	string login;
	string hashOfPassword;
	bool blocked;
};

#endif

