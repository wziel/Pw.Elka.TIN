#ifndef I_ADMIN_DAL
#define I_ADMIN_DAL

#include <string>
#include<vector>
#include "../Shared/ClientModel.h"

using namespace std;

class IAdminDAL
{
public:
	virtual ~IAdminDAL() {};
	virtual bool BlockClient(string login, bool isBlocked) = 0;
	virtual bool CreateClient(string login, string hashOfPassword) = 0;
	virtual bool DeleteClient(string login) = 0;
	virtual bool ChangeLogin(int clientId, string newLogin) = 0;
	virtual std::vector<ClientModel> GetAllClients() = 0;
	virtual bool ModifyClient(string oldLogin, string login, string passwordHash) = 0;
};

#endif