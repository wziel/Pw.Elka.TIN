#ifndef I_CLIENT_DAL
#define I_CLIENT_DAL

#include <string>
#include <vector>

#include "../../Header Files/Shared/MessageModel.h"
#include "../../Header Files/Shared/GroupModel.h"
#include "../../Header Files/Shared/ClientModel.h"
#include "../../Header Files/Interfaces/IDAL.h"

using namespace std;

//class MessageModel;
//class GroupModel;

class IClientDAL
	:public IDAL
{
public:
	virtual ~IClientDAL() {};
	virtual MessageModel GetMessageById(int id, int clientId) = 0;
	virtual MessageModel CreateMessage (string title, string content, int clientId) = 0;
	virtual MessageModel ModifyMessage(int id, string title, string content, int clientId) = 0;
	virtual bool DeleteMessage(int id, int clientId) = 0;
	virtual vector<MessageModel> GetAllMessagesWithoutContent(int clientId) = 0;
	virtual vector<GroupModel> GetAllGroupsWithoutAdresses(int clientId) = 0;
	virtual GroupModel GetGroupById(int id, int clientId) = 0;
	virtual bool DeleteGroupById(int id, int clientId) = 0;
	virtual GroupModel CreateGroup(string name, int clientId) = 0;
	virtual bool AddAddressToGroup(int groupId, int addressId, int clientId) = 0;
	virtual bool RemoveAddressFromGroup(int groupId, int addressId, int clientId) = 0;
	virtual string GetHashOfPassword(string username) = 0;
	virtual AddressModel CreateAddress(string addrName, string addrValue, int clientId) = 0;
	virtual bool DeleteAddress(int addrId, int clientId) = 0;
	virtual vector<AddressModel> GetAllAddresses(int clientId) = 0;
	virtual ClientModel getClient(string login) = 0;
	//IDAL
	virtual bool ChangeHashOfPassword(string login, string newHashOfPassword)=0;
};

#endif
