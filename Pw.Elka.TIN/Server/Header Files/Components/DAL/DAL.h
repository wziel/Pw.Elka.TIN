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
	///returns true if succeeded
	bool CreateClient(string login, string hashOfPassword);
	///returns true if succeeded
	bool DeleteClient(string login);
	///returns true if succeeded
	bool ChangeLogin(string login, string newLogin);
	///returns vector of all objects
	std::vector<ClientModel> GetAllClients();
	///returns true if succeeded 
	bool UnblockClient(string login);

	//IClientDAL.h
	///if returned object's id is less than 0 then operation didn't success
	MessageModel GetMessageById(int id, int clientId);
	///if returned object's id is less than 0 then operation didn't success
	MessageModel CreateMessage(string title, string content, int clientId);
	///if returned object's id is less than 0 then operation didn't success
	MessageModel ModifyMessage(int id, string title, string content, int clientId);
	///returns true if succeeded 
	bool DeleteMessage(int id, int clientId);
	///returns vector of all objects
	vector<MessageModel> GetAllMessagesWithoutContent(int clientId);
	///returns vector of all objects
	vector<GroupModel> GetAllGroupsWithoutAdresses(int clientId);
	///if returned object's id is less than 0 then operation didn't success
	GroupModel GetGroupById(int id, int clientId);
	///returns true if succeeded 
	bool DeleteGroupById(int id, int clientId);
	///if returned object's id is less than 0 then operation didn't success
	GroupModel CreateGroup(string name, int clientId);
	///returns true if succeeded 
	bool AddAddressToGroup(int groupId, int addressId, int clientId);
	///returns true if succeeded 
	bool RemoveAddressFromGroup(int groupId, int addressId, int clientId);
	///returns empty string when failed
	string GetHashOfPassword(string username);
	///returns true if succeeded 
	bool IsBlocked(int clientId);
	///if returned object's id is less than 0 then operation didn't success
	AddressModel CreateAddress(string addrName, string addrValue, int clientId);
	///returns true if succeeded 
	bool DeleteAddress(int addrId, int clientId);
	///returns vector of all objects
	vector<AddressModel> GetAllAddresses(int clientId);
	///if returned object's id is less than 0 then operation didn't success
	ClientModel getClient(string login);

	//IDAL.h
	///returns true if succeeded 
	bool ChangeHashOfPassword(string login, string newHashOfPassword);
	///returns true if succeeded 
	bool BlockClient(string login);
	


};

