#pragma once
#include "../../Interfaces/IDAL.h"
#include "../../Interfaces/IAdminDAL.h"
#include "../../Interfaces/IClientDAL.h"
class DAL :
	public IClientDAL, public IAdminDAL, public IDAL
{
public:
	DAL();
	~DAL();
/*********************/
/*Ceated for testing!*/
/*********************/
//IClientDAL.h 
	string GetHashOfPassword(string username);
/*********************/

	//IAdminDAL.h
    bool BlockClient(string login, bool isBlocked);
	bool CreateClient(string login, string hashOfPassword);
	bool DeleteClient(string login);
	bool ChangeLogin(int clientId, string newLogin);
	std::vector<ClientModel> GetAllClients();
	bool ModifyClient(string oldLogin, string login, string passwordHash);

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
	bool AddAddressToGroup(int groupId, string value, int clientId);
	bool RemoveAddressFromGroup(int groupId, int addressId, int clientId);
	//string GetHashOfPassword(string username);
	bool IsBlocked(int clientId);

	//IDAL.h
	bool ChangeHashOfPassword(int clientId, string newHashOfPassword);
	bool BlockClient(string login);
};

