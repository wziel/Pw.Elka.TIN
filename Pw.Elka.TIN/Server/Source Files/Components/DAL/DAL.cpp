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
	/* MOCK */

	return true;
}
bool DAL::CreateClient(string login, string hashOfPassword)
{
	/* MOCK */

	return true;
}
bool DAL::DeleteClient(string login)
{
	/* MOCK */

	return true;
}
bool DAL::ChangeLogin(int clientId, string newLogin)
{
	/* MOCK */

	return true;
}
vector<ClientModel> DAL::GetAllClients()
{
	/* MOCK */

	vector<ClientModel> klienci;

	ClientModel klient1(1, "Michal", "hashHasla");
	ClientModel klient2(2, "Asia", "hashHasla");
	ClientModel klient3(3, "Wojtek", "hashHasla");

	klienci.push_back(klient1);
	klienci.push_back(klient2);
	klienci.push_back(klient3);

	return klienci;
}
bool DAL::ModifyClient(string oldLogin, string login, string passwordHash)
{
	/* MOCK */

	return true;
}

//IClientDAL.h
MessageModel DAL::GetMessageById(int id, int clientId)
{
	/* MOCK */

	MessageModel wiadomosc1(1, "Wiadomosc1", "To jest bardzo superowa wiadomosc, ktora mozna sobie wyslac lub tez nie. Albo lepiej komus a nie sobie");
	return wiadomosc1;
}
MessageModel DAL::CreateMessage(string title, string content, int clientId)
{
	/* MOCK */

	MessageModel wiadomosc1(1, "Wiadomosc1", "");
	return wiadomosc1;
}
MessageModel DAL::ModifyMessage(int id, string title, string content, int clientId)
{
	/* MOCK */

	MessageModel wiadomosc1(1, title, content);
	return wiadomosc1;
}
bool DAL::DeleteMessage(int id, int clientId)
{
	/* MOCK */

	return true;
}
vector<MessageModel> DAL::GetAllMessagesWithoutContent(int clientId)
{
	/* MOCK */

	MessageModel wiadomosc1(1, "Wiadomosc1", "");
	MessageModel wiadomosc2(2, "Wiadomosc2", "");
	MessageModel wiadomosc3(3, "Wiadomosc3", "");

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
	/* MOCK */

	vector<AddressModel> adresy;

	AddressModel adres1(1, "michal@gmail.com", "Michal");
	AddressModel adres2(2, "asia@gmail.com", "Asia");
	AddressModel adres3(3, "wojtek@gmail.com", "Wojtek");

	adresy.push_back(adres1);
	adresy.push_back(adres2);
	adresy.push_back(adres3);

	GroupModel grupa1(1, "Grupa1", adresy);

	return grupa1;
}
bool DAL::DeleteGroupById(int id, int clientId)
{
	/* MOCK */

	return true;
}
GroupModel DAL::CreateGroup(string name, int clientId)
{
	/* MOCK */

	vector<AddressModel> adresy;
	GroupModel grupa1(1, "Grupa1", adresy);

	return grupa1;
}
bool DAL::AddAddressToGroup(int groupId, int addressId, int clientId)
{
	/* MOCK */

	return true;
}
bool DAL::RemoveAddressFromGroup(int groupId, int addressId, int clientId)
{
	/* MOCK */

	return true;
}
string DAL::GetHashOfPassword(string username)
{
	/* MOCK */

	return string("test");
}
bool DAL::IsBlocked(int clientId)
{
	/* MOCK */

	return false;
}
AddressModel DAL::CreateAddress(string addrName, string addrValue, int clientId)
{
	/* MOCK */

	return *new AddressModel(8,addrValue, addrName);
}
bool DAL::DeleteAddress(int addrId, int clientId)
{
	/* MOCK */

	return true;
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
	/* MOCK */

	return true;
}
bool DAL::BlockClient(string login)
{
	/* MOCK */

	return true;
}
ClientModel DAL::getClient(string login)
{
	/* MOCK */

	return *(new ClientModel(1, login, "test"));
}