#pragma once

#include <odbc++\drivermanager.h>
#include <odbc++\connection.h>
#include <odbc++\resultset.h>
#include <odbc++\resultsetmetadata.h>
#include <odbc++\callablestatement.h>
#include <odbc++\databasemetadata.h>

#include "../../Interfaces/IDAL.h"
#include "../../Interfaces/IAdminDAL.h"
#include "../../Interfaces/IClientDAL.h"

using namespace odbc;

class DAL :
	public IClientDAL, public IAdminDAL
{

private:
	Connection* connection;
	DriverManager*	driverManager;
public:
	DAL();
	~DAL();
	Connection getConnection();

	//IAdminDAL.h
    bool BlockClient(string login, bool isBlocked);
	bool CreateClient(string login, string hashOfPassword);
	bool DeleteClient(string login);
	bool ChangeLogin(string login, string newLogin);
	std::vector<ClientModel> GetAllClients();
	bool UnblockClient(string login);

	//IClientDAL.h
	MessageModel GetMessageById(int id, int clientId);
	MessageModel CreateMessage(string title, string content, int clientId);
	MessageModel ModifyMessage(int id, string title, string content, int clientId);
	bool DeleteMessage(int id, int clientId);
	vector<MessageModel> GetAllMessagesWithoutContent(int clientId);
	vector<GroupModel> GetAllGroupsWithoutAdresses(int clientId);
	GroupModel GetGroupById(int id, int clientId);
	bool DeleteGroupById(int id, int clientId);
	GroupModel CreateGroup(string name, int clientId);
	bool AddAddressToGroup(int groupId, int addressId, int clientId);
	bool RemoveAddressFromGroup(int groupId, int addressId, int clientId);
	string GetHashOfPassword(string username);
	bool IsBlocked(int clientId);
	AddressModel CreateAddress(string addrName, string addrValue, int clientId);
	bool DeleteAddress(int addrId, int clientId);
	vector<AddressModel> GetAllAddresses(int clientId);
	ClientModel getClient(string login);

	//IDAL.h
	bool ChangeHashOfPassword(string login, string newHashOfPassword);
	bool BlockClient(string login);
	


};

