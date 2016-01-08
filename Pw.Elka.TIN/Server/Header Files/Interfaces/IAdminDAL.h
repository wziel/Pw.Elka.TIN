#ifndef I_ADMIN_DAL
#define I_ADMIN_DAL

#include <string>
#include<vector>
#include "../Shared/ClientModel.h"
#include "IDAL.h"

using namespace std;

class IAdminDAL
	:IDAL
{
public:
	virtual ~IAdminDAL() {};
	virtual bool CreateClient(string login, string hashOfPassword) = 0;
	virtual bool DeleteClient(string login) = 0;
	virtual bool ChangeLogin(string login, string newLogin) = 0;
	virtual std::vector<ClientModel> GetAllClients() = 0;
	virtual bool UnblockClient(string login) = 0;

	//IDAL
	virtual bool ChangeHashOfPassword(string login, string newHashOfPassword) = 0;
	virtual bool BlockClient(string login) = 0;
};

#endif