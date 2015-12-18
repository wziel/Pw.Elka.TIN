#ifndef CLIENT_MODEL
#define CLIENT_MODEL

#include <string>

using namespace std;

class ClientModel
{
public:
	ClientModel() {}
	ClientModel(int id, string login, string hashOfPassword) : id(id), login(login), hashOfPassword(hashOfPassword) {}
	~ClientModel() {}

	int id;
	string login;
	string hashOfPassword;
};

#endif

