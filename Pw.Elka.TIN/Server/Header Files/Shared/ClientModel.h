#ifndef CLIENT_MODEL
#define CLIENT_MODEL

#include <string>

using namespace std;

class ClientModel
{
public:
	ClientModel() {}
	ClientModel(int id, string login, string hashOfPassword, bool blocked) : id(id), login(login), hashOfPassword(hashOfPassword), blocked(blocked) {}
	~ClientModel() {}

	int id;
	string login;
	string hashOfPassword;
	bool blocked;
};

#endif

