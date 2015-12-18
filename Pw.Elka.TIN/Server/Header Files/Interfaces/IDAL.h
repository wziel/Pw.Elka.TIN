#ifndef I_DAL
#define I_DAL

#include <string>

using namespace std;

class IDAL
{
public:
	virtual bool ChangeHashOfPassword(int clientId, string newHashOfPassword) = 0;
	virtual bool BlockClient(string login) = 0;
};

#endif