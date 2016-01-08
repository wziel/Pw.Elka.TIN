#include "../../../Header Files/Components/DAL/DAL.h"

DAL::DAL()
{
}


DAL::~DAL()
{
}

//IAdminDAL.h
bool DAL::BlockClient(string login, bool isBlocked)
{
	throw "Not implemented";
}
bool DAL::CreateClient(string login, string hashOfPassword)
{
	throw "Not implemented";
}
bool DAL::DeleteClient(string login)
{
	throw "Not implemented";
}
bool DAL::ChangeLogin(int clientId, string newLogin)
{
	throw "Not implemented";
}
std::vector<ClientModel> DAL::GetAllClients()
{
	throw "Not implemented";
}
bool DAL::ModifyClient(string oldLogin, string login, string passwordHash)
{
	throw "Not implemented";
}

//IClientDAL.h
MessageModel DAL::GetMessageById(int id, int clientId)
{
	throw "Not implemented";
}
MessageModel DAL::CreateMessage(string title, string content, int clientId)
{
	throw "Not implemented";
}
MessageModel DAL::ModifyMessage(int id, string title, string content, int clientId)
{
	throw "Not implemented";
}
bool DAL::DeleteMessage(int id, int clientId)
{
	throw "Not implemented";
}
vector<MessageModel> DAL::GetAllMessagesWithoutContent(int clientId)
{
	throw "Not implemented";
}
vector<GroupModel> DAL::GetAllGroupsWithoutAdresses(int clientId)
{
	throw "Not implemented";
}
GroupModel DAL::GetGroupById(int id, int clientId)
{
	throw "Not implemented";
}
bool DAL::DeleteGroupById(int id, int clientId)
{
	throw "Not implemented";
}
GroupModel DAL::CreateGroup(string name, int clientId)
{
	throw "Not implemented";
}
bool DAL::AddAddressToGroup(int groupId, int addressId, int clientId)
{
	throw "Not implemented";
}
bool DAL::RemoveAddressFromGroup(int groupId, int addressId, int clientId)
{
	throw "Not implemented";
}
string DAL::GetHashOfPassword(string username)
{
	return string("test");
}
bool DAL::IsBlocked(int clientId)
{
	throw "Not implemented";
}
AddressModel DAL::CreateAddress(string addrName, string addrValue, int clientId)
{
	return *new AddressModel(8,addrValue, addrName);
}
bool DAL::DeleteAddress(int addrId, int clientId)
{
	throw "Not implemented";
}
vector<AddressModel> DAL::GetAllAddresses(int clientId)
{
	throw "Not implemented";
}

//IDAL.h
bool DAL::ChangeHashOfPassword(int clientId, string newHashOfPassword)
{
	throw "Not implemented";
}
bool DAL::BlockClient(string login)
{
	throw "Not implemented";
}
ClientModel DAL::getClient(string login)
{
	return *(new ClientModel(1, login, "test"));
}