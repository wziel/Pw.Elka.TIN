#ifndef I_CLIENT_DAL
#define I_CLIENT_DAL

#include <string>
#include <vector>

using namespace std;

class MessageModel;
class GroupModel;

class IClientDAL
{
public:
	virtual ~IClientDAL() = 0;
	virtual MessageModel GetMessageById(int id, int clientId) = 0;
	virtual MessageModel CreateMessage (string title, string content, int clientId) = 0;
	virtual MessageModel ModifyMessage(int id, string title, string content, int clientId) = 0;
	virtual bool DeleteMessage(int id, int clientId) = 0;
	virtual vector<MessageModel> GetAllMessagesWithoutContent(int clientId) = 0;
	virtual vector<GroupModel> GetAllGroupsWithoutAdresses(int clientId) = 0;
	virtual GroupModel GetGroupById(int id, int clientId) = 0;
	virtual bool DeleteGroupById(int id, int clientId) = 0;
	virtual GroupModel CreateGroup(string name, int clientId) = 0;
	virtual bool AddAddressToGroup(int groupId, string value, int clientId) = 0;
	virtual bool RemoveAddressFromGroup(int groupId, int addressId, int clientId) = 0;
	virtual string GetHashOfPassword(string username) = 0;
	virtual bool IsBlocked(int clientId) = 0;
};

#endif
