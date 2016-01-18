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


	// DESCRIPTION: use in every SQL query to handle SQLexceptions
	///    RETURNS: returns true if execution succeeeded
	bool ExecutePreparedStatement(PreparedStatement *preparedStatement);

public:
	DAL();
	~DAL();
	Connection getConnection();

	//IAdminDAL.h
	// DESCRIPTION: use to create new user
	///     RETURNS:  true if succeeded
	bool CreateClient(string login, string hashOfPassword);

	// DESCRIPTION: use to delete user who exist in DB
	///     RETURNS:  true if succeeded
	bool DeleteClient(string login);

	// DESCRIPTION: use to change user's login if it exist
	///     RETURNS:  true if succeeded
	bool ChangeLogin(string login, string newLogin);

	// DESCRIPTION: use id we want to get all clients
	///     RETURNS:  vector of all objects
	std::vector<ClientModel> GetAllClients();

	// DESCRIPTION: use to unblock user
	///     RETURNS:  true if succeeded
	bool UnblockClient(string login);

	//IClientDAL.h
	// DESCRIPTION: use to get message by ID
	///     RETURNS:  if returned object's id is less than 0 then operation didn't success
	MessageModel GetMessageById(int id, int clientId);

	// DESCRIPTION: use create new message
	///     RETURNS:  if returned object's id is less than 0 then operation didn't success
	MessageModel CreateMessage(string title, string content, int clientId);

	// DESCRIPTION: use to modyfy existing message
	///     RETURNS:  if returned object's id is less than 0 then operation didn't success
	MessageModel ModifyMessage(int id, string title, string content, int clientId);

	// DESCRIPTION: use to delete existing message
	///     RETURNS:  true if succeeded
	bool DeleteMessage(int id, int clientId);

	// DESCRIPTION: use to list all message from one clinet
	///     RETURNS:  vector of all objects
	vector<MessageModel> GetAllMessagesWithoutContent(int clientId);

	// DESCRIPTION: use to list all groups
	///     RETURNS:  returns vector of all objects
	vector<GroupModel> GetAllGroupsWithoutAdresses(int clientId);

	// DESCRIPTION: use to get group by ID
	///     RETURNS: if returned object's id is less than 0 then operation didn't success
	GroupModel GetGroupById(int id, int clientId);

	// DESCRIPTION: use to delete group by ID
	///     RETURNS:  returns true if succeeded 
	bool DeleteGroupById(int id, int clientId);

	// DESCRIPTION: use to create new group
	///     RETURNS:  if returned object's id is less than 0 then operation didn't success
	GroupModel CreateGroup(string name, int clientId);

	// DESCRIPTION: use to attach address to group
	///     RETURNS:  true if succeeded
	bool AddAddressToGroup(int groupId, int addressId, int clientId);

	// DESCRIPTION: use detach address from group
	///     RETURNS:  true if succeeded
	bool RemoveAddressFromGroup(int groupId, int addressId, int clientId);

	// DESCRIPTION: use to get hash of password from DB
	///     RETURNS:  empty string when failed
	string GetHashOfPassword(string username);

	// DESCRIPTION: use to create new address
	///     RETURNS:  if returned object's id is less than 0 then operation didn't success
	AddressModel CreateAddress(string addrName, string addrValue, int clientId);

	// DESCRIPTION: use to delete address
	///     RETURNS:  true if succeeded
	bool DeleteAddress(int addrId, int clientId);

	// DESCRIPTION: use to list all addresses
	///     RETURNS:  returns vector of all objects
	vector<AddressModel> GetAllAddresses(int clientId);

	// DESCRIPTION: use to get client by login if exist
	///     RETURNS:  if returned object's id is less than 0 then operation didn't success
	ClientModel getClient(string login);

	//IDAL.h
	// DESCRIPTION: use to change password stored in DB
	///     RETURNS:  true if succeeded
	bool ChangeHashOfPassword(string login, string newHashOfPassword);

	// DESCRIPTION: use to block user
	///     RETURNS:  true if succeeded
	bool BlockClient(string login);
};

