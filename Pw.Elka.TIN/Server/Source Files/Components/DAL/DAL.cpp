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
	/* MOCK */

	MessageModel wiadomosc1(1, "Wiadomosc1", NULL);
	MessageModel wiadomosc2(2, "Wiadomosc2", NULL);
	MessageModel wiadomosc3(3, "Wiadomosc3", NULL);

	vector<MessageModel> wiadomosci;
	wiadomosci.push_back(wiadomosc1);
	wiadomosci.push_back(wiadomosc2);
	wiadomosci.push_back(wiadomosc3);

	return wiadomosci;
}
vector<GroupModel> DAL::GetAllGroupsWithoutAdresses(int clientId)
{
	/* MOCK */

	vector<AddressModel> adresy;

	GroupModel grupa1(1, "Grupa1", adresy);
	GroupModel grupa2(2, "Grupa2", adresy);
	GroupModel grupa3(3, "Grupa3", adresy);

	vector<GroupModel> grupy;
	grupy.push_back(grupa1);
	grupy.push_back(grupa2);
	grupy.push_back(grupa3);

	return grupy;
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

	/* MOCK */

	AddressModel adres1(1, "michal@gmail.com", "Michal");
	AddressModel adres2(2, "asia@gmail.com", "Asia");
	AddressModel adres3(3, "wojtek@gmail.com", "Wojtek");

	vector<AddressModel> adresy;
	adresy.push_back(adres1);
	adresy.push_back(adres2);
	adresy.push_back(adres3);

	return adresy;
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