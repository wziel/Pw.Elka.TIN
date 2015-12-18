#ifndef I_ADMIN_DAL
#define I_ADMIN_DAL

#include <string>

using namespace std;

class IAdminDAL
{
public:
	virtual bool UnblockClient(string login) = 0;
	virtual bool CreateClient(string login, string password) = 0;
	virtual bool DeleteClient(string login) = 0;
	virtual bool ChangeLogin(int clientId, string newLogin) = 0;
};

#endif