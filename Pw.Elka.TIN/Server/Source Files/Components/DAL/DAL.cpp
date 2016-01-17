#include "../../../Header Files/Components/DAL/DAL.h"

DAL::DAL()
{

	connection = driverManager->getConnection("DSN=LokalnaBazaDanychTIN");

}


DAL::~DAL()
{
}

Connection DAL::getConnection()
{
	return *connection;
}

bool DAL::ExecutePreparedStatement(PreparedStatement *preparedStatement)
{
	try
	{
		preparedStatement->execute();
		return true;
	}
	catch (exception e)
	{
		return false;
	}
}
// sprawdz to bo nie wierze ze to dziala
bool DAL::CreateClient(string login, string hashOfPassword)
{
	//int clientId;
	//ResultSet *resultSet;
	PreparedStatement *preparedStatement;

	//if (getClient(login).id < 0) return false;

	string part1 = "INSERT INTO LokalnaBazaDanychTIN.dbo.Client ( login, password_hash , blocked ) VALUES( '";
	//string part2 = " Select IDENT_CURRENT( 'LokalnaBazaDanychTIN.dbo.Client' ) AS last_inserted_row ";


	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + login + "' , '" + hashOfPassword + "' ,  0  )"));
	if (ExecutePreparedStatement(preparedStatement) == false) return false;

	//preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part2));
	//if (ExecutePreparedStatement(preparedStatement) == false) return false;

	//resultSet = preparedStatement->getResultSet();
	//if (resultSet->next() == false) return false;

	//clientId = resultSet->getInt("last_inserted_row");
	return true;
}
//// Przetestuj
bool DAL::DeleteClient(string login)
{	
	if (getClient(login).id < 0) return false;

	ClientModel client = this->getClient(login);
	PreparedStatement *preparedStatement;
	string  sClientId ;
	ostringstream konwersja;
	konwersja << client.id;
	sClientId = konwersja.str();
	konwersja.str("");
	konwersja.clear();

	string part1 = "DELETE FROM LokalnaBazaDanychTIN.dbo.Address Where LokalnaBazaDanychTIN.dbo.Address.id_client = ";
	string part2 = "DELETE FROM LokalnaBazaDanychTIN.dbo.Client WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sClientId  ));
	if (ExecutePreparedStatement(preparedStatement) == false) return false;
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part2 + login + "'"));
	if (ExecutePreparedStatement(preparedStatement) == false) return false;

	return true;
}
bool DAL::ChangeLogin(string login, string newLogin)
{
	if (getClient(login).id < 0) return false;
	PreparedStatement *preparedStatement;

	string part1 = "UPDATE LokalnaBazaDanychTIN.dbo.Client SET LokalnaBazaDanychTIN.dbo.Client.login = '";
	string part2 = "' WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + newLogin + part2 + login + "'"));
	if (ExecutePreparedStatement(preparedStatement) == false) return false;

	return true;
}
vector<ClientModel> DAL::GetAllClients()
{
	int clientId;
	string login, hash;
	bool blocked;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	vector<ClientModel>  vector;

	string part1 = "SELECT * FROM LokalnaBazaDanychTIN.dbo.Client ";
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1));
	if (ExecutePreparedStatement(preparedStatement) == false) return vector;
	resultSet = preparedStatement->getResultSet();

	while (resultSet->next())
	{
		clientId = resultSet->getInt("id_client");
		login = resultSet->getString("login");
		hash = resultSet->getString("password_hash");
		blocked = resultSet->getBoolean("blocked");
		vector.push_back(ClientModel(clientId, login, hash, blocked));

	}

	return  vector;
}

bool  DAL::UnblockClient(string login)
{
	PreparedStatement *preparedStatement;

	if (getClient(login).id < 0) return false;

	string part1 = "UPDATE LokalnaBazaDanychTIN.dbo.Client SET LokalnaBazaDanychTIN.dbo.Client.blocked = 0 WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + login + "'"));
	if (ExecutePreparedStatement(preparedStatement) == false) return false;

	return true;
}

//IClientDAL.h
MessageModel DAL::GetMessageById(int mssageId, int clientId)
{
	string title;
	string content;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sClientId, sId;
	ostringstream konwersja;
	konwersja << clientId;
	sClientId = konwersja.str();
	konwersja.str("");
	konwersja.clear();
	konwersja << mssageId;
	sId = konwersja.str();

	string part1 = "SELECT *  FROM  LokalnaBazaDanychTIN.dbo.Message WHERE id_client = ";
	string part2 = " AND  id_message = ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sClientId + part2 + sId));
	if (ExecutePreparedStatement(preparedStatement) == false) return MessageModel(-1, "");

	resultSet = preparedStatement->getResultSet();
	if (resultSet->next() == false) return MessageModel(-1, "");

	title = resultSet->getString("title");
	content = resultSet->getString("content");

	return  MessageModel(mssageId, title, content);
}
MessageModel DAL::CreateMessage(string title, string content, int clientId)
{
	int messageId;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sClientId;
	ostringstream konwersja;
	konwersja << clientId;
	sClientId = konwersja.str();
	konwersja.str("");
	konwersja.clear();

	string part1 = "INSERT INTO LokalnaBazaDanychTIN.dbo.Message (id_client, title, content) VALUES( ";
	string part2 = " Select IDENT_CURRENT( 'LokalnaBazaDanychTIN.dbo.Message' ) AS last_inserted_row ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sClientId + " , '" + title + "' , '" + content + "' )"));
	if (ExecutePreparedStatement(preparedStatement) == false) return MessageModel(-1, "");

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part2));
	if (ExecutePreparedStatement(preparedStatement) == false) return MessageModel(-1, "");

	resultSet = preparedStatement->getResultSet();
	if (resultSet->next() == false) return MessageModel(-1, "");

	messageId = resultSet->getInt("last_inserted_row");
	
	return  MessageModel(messageId, title, content);
}
MessageModel DAL::ModifyMessage(int messageId, string title, string content, int clientId)
{
	PreparedStatement *preparedStatement;
	string  sClientId, sMessageId;
	ostringstream konwersja;
	konwersja << clientId;
	sClientId = konwersja.str();
	konwersja.str("");
	konwersja.clear();
	konwersja << messageId;
	sMessageId = konwersja.str();

	string part1 = "UPDATE LokalnaBazaDanychTIN.dbo.Message SET LokalnaBazaDanychTIN.dbo.Message.title = '";
	string part2 = "', LokalnaBazaDanychTIN.dbo.Message.content = '";
	string part3 = "', LokalnaBazaDanychTIN.dbo.Message.id_client = '";
	string part4 = "' WHERE LokalnaBazaDanychTIN.dbo.Message.id_message = ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + title + part2 + content + part3 + sClientId + part4 + sMessageId));
	if (ExecutePreparedStatement(preparedStatement) == false) return MessageModel(-1, "");

	return  MessageModel(messageId, title, content);
}
bool DAL::DeleteMessage(int messageId, int clientId)
{
	PreparedStatement *preparedStatement;
	string  sClientId, sMessageId;
	ostringstream konwersja;
	konwersja << clientId;
	sClientId = konwersja.str();
	konwersja.str("");
	konwersja.clear();
	konwersja << messageId;
	sMessageId = konwersja.str();

	string part1 = "DELETE FROM LokalnaBazaDanychTIN.dbo.Message WHERE LokalnaBazaDanychTIN.dbo.Message.id_message = ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sMessageId));
	if (ExecutePreparedStatement(preparedStatement) == false) return false;

	return true;
}
vector<MessageModel> DAL::GetAllMessagesWithoutContent(int clientId)
{
	int messageId;
	string title;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sClientId;
	ostringstream konwersja;
	vector<MessageModel> vector;
	konwersja << clientId;
	sClientId = konwersja.str();
	konwersja.str("");
	konwersja.clear();

	string part1 = "SELECT LokalnaBazaDanychTIN.dbo.Message.id_message, LokalnaBazaDanychTIN.dbo.Message.title FROM LokalnaBazaDanychTIN.dbo.Message WHERE LokalnaBazaDanychTIN.dbo.Message.id_client = ";
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sClientId));
	if (ExecutePreparedStatement(preparedStatement) == false) return vector;

	resultSet = preparedStatement->getResultSet();

	while (resultSet->next())
	{
		messageId = resultSet->getInt("id_message");
		title = resultSet->getString("title");
		vector.push_back(MessageModel(messageId, title));

	}

	return  vector;
}

vector<GroupModel> DAL::GetAllGroupsWithoutAdresses(int clientId)
{
	int groupId;
	string  nameOfGroup;
	vector<GroupModel> groups;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sClientId;
	ostringstream konwersja;
	konwersja << clientId;
	sClientId = konwersja.str();
	konwersja.str("");
	konwersja.clear();

	string part1 = " SELECT * FROM LokalnaBazaDanychTIN.dbo.[Group] WHERE LokalnaBazaDanychTIN.dbo.[Group].id_client = ";
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sClientId));
	if (ExecutePreparedStatement(preparedStatement) == false) return groups;

	resultSet = preparedStatement->getResultSet();

	while (resultSet->next())
	{
		groupId = resultSet->getInt("id_group");
		nameOfGroup = resultSet->getString("name");
		groups.push_back(GroupModel(groupId, nameOfGroup));
	}
	return  groups;
}
// nie u¿ywam clientId
GroupModel DAL::GetGroupById(int groupId, int clientId)
{
	int addressId;
	string value, addresseeName, nameOfGroup;
	vector<AddressModel> addresses;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sClientId, sGroupId;
	ostringstream konwersja;
	konwersja << clientId;
	sClientId = konwersja.str();
	konwersja.str("");
	konwersja.clear();
	konwersja << groupId;
	sGroupId = konwersja.str();

	string part1 = "Select  *  From LokalnaBazaDanychTIN.dbo.Group_Address JOIN LokalnaBazaDanychTIN.dbo.Address ON LokalnaBazaDanychTIN.dbo.Group_Address.id_address = LokalnaBazaDanychTIN.dbo.Address.id_address Where LokalnaBazaDanychTIN.dbo.Group_Address.id_group = ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sGroupId));
	if (ExecutePreparedStatement(preparedStatement) == false) return GroupModel(-1, "");
	resultSet = preparedStatement->getResultSet();

	while (resultSet->next())
	{
		addressId = resultSet->getInt("id_address");
		addresseeName = resultSet->getString("addressee_name");
		value = resultSet->getString("address_name");

		addresses.push_back(AddressModel(addressId, value, addresseeName));
	}
	
	string part2 = " SELECT LokalnaBazaDanychTIN.dbo.[Group].name FROM LokalnaBazaDanychTIN.dbo.[Group] WHERE LokalnaBazaDanychTIN.dbo.[Group].id_group = ";
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part2 + sGroupId));
	if (ExecutePreparedStatement(preparedStatement) == false) return GroupModel(-1, "");

	resultSet = preparedStatement->getResultSet();
	if (resultSet->next() == false) return GroupModel(-1, "");

	nameOfGroup = resultSet->getString("name");

	return  GroupModel(groupId, nameOfGroup, addresses);
}

bool DAL::DeleteGroupById(int groupId, int clientId)
{
//	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sGroupId;
	ostringstream konwersja;
	konwersja << groupId;
	sGroupId = konwersja.str();
	konwersja.str("");
	konwersja.clear();

	string part1 = "DELETE FROM LokalnaBazaDanychTIN.dbo.[Group] WHERE LokalnaBazaDanychTIN.dbo.[Group].id_group = ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sGroupId));
	if (ExecutePreparedStatement(preparedStatement) == false) return false;

	return true;
}

GroupModel DAL::CreateGroup(string name, int clientId)
{

	int groupId;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sClientId;
	ostringstream konwersja;
	konwersja << clientId;
	sClientId = konwersja.str();
	konwersja.str("");
	konwersja.clear();

	string part1 = " INSERT INTO LokalnaBazaDanychTIN.dbo.[Group]( id_client , name ) VALUES( ";
	string part2 = "Select IDENT_CURRENT('LokalnaBazaDanychTIN.dbo.[Group]') AS last_inserted_row";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sClientId + " , '" + name + "' )"));
	if (ExecutePreparedStatement(preparedStatement) == false) return GroupModel(-1, "");

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part2));
	if (ExecutePreparedStatement(preparedStatement) == false) return GroupModel(-1, "");

	resultSet = preparedStatement->getResultSet();
	if (resultSet->next() == false) return GroupModel(-1, "");

	groupId = resultSet->getInt("last_inserted_row");

	return GroupModel(groupId, name);
}
bool DAL::AddAddressToGroup(int groupId, int addressId, int clientId)
{
//	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sGroupId, sAddressId;
	ostringstream konwersja;
	konwersja << groupId;
	sGroupId = konwersja.str();
	konwersja.str("");
	konwersja.clear();
	konwersja << addressId;
	sAddressId = konwersja.str();

	string part1 = "INSERT INTO LokalnaBazaDanychTIN.dbo.Group_Address(id_group, id_address) VALUES( ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sGroupId + " , " + sAddressId + " )"));
	if (ExecutePreparedStatement(preparedStatement) == false) return false;

	return true;
}
bool DAL::RemoveAddressFromGroup(int groupId, int addressId, int clientId)
{
//	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sGroupId, sAddressId;
	ostringstream konwersja;
	konwersja << groupId;
	sGroupId = konwersja.str();
	konwersja.str("");
	konwersja.clear();
	konwersja << addressId;
	sAddressId = konwersja.str();

	string part1 = "DELETE FROM LokalnaBazaDanychTIN.dbo.Group_Address WHERE LokalnaBazaDanychTIN.dbo.Group_Address.id_group = ";
	string part2 = " AND LokalnaBazaDanychTIN.dbo.Group_Address.id_address = ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sGroupId + part2 + sAddressId));
	if (ExecutePreparedStatement(preparedStatement) == false) return false;

	return true;
}
string DAL::GetHashOfPassword(string login)
{

	string hash;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;

	if (getClient(login).id < 0) return false;

	string part1 = "SELECT LokalnaBazaDanychTIN.dbo.Client.password_hash  FROM  LokalnaBazaDanychTIN.dbo.Client WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + login + " ' "));
	if (ExecutePreparedStatement(preparedStatement) == false) return "";

	resultSet = preparedStatement->getResultSet();
	if (resultSet->next() == false) return "";

	hash = resultSet->getString("password_hash");

	return  hash;
}
AddressModel DAL::CreateAddress(string addrName, string addrValue, int clientId)
{
	int messageId;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sClientId;
	ostringstream konwersja;
	konwersja << clientId;
	sClientId = konwersja.str();
	konwersja.str("");
	konwersja.clear();

	string part1 = "INSERT INTO LokalnaBazaDanychTIN.dbo.Address(addressee_name, address_name , id_client) VALUES('";
	string part2 = "Select IDENT_CURRENT('LokalnaBazaDanychTIN.dbo.Address') AS last_inserted_row";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + addrName + "' , '" + addrValue + "', " + sClientId + " )"));
	if (ExecutePreparedStatement(preparedStatement) == false) return AddressModel(-1, "", "");

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part2));
	if (ExecutePreparedStatement(preparedStatement) == false) return AddressModel(-1, "", "");

	resultSet = preparedStatement->getResultSet();
	if (resultSet->next() == false) return AddressModel(-1, "", "");

	messageId = resultSet->getInt("last_inserted_row");

	return AddressModel(messageId, addrValue, addrName);
}
bool DAL::DeleteAddress(int addrId, int clientId)
{
//	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sAddrId, sClientId;
	ostringstream konwersja;
	konwersja << addrId;
	sAddrId = konwersja.str();
	konwersja.str("");
	konwersja.clear();
	konwersja << addrId;
	sAddrId = konwersja.str();

	string part1 = "DELETE FROM LokalnaBazaDanychTIN.dbo.Address WHERE LokalnaBazaDanychTIN.dbo.Address.id_address = ";
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sAddrId));
	if (ExecutePreparedStatement(preparedStatement) == false) return false;

	return true;
}
vector<AddressModel> DAL::GetAllAddresses(int clientId)
{
	int addressId;
	string name, value;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sClientId;
	ostringstream konwersja;
	vector<AddressModel> vector;
	konwersja << clientId;
	sClientId = konwersja.str();
	konwersja.str("");
	konwersja.clear();
	string part1 = "SELECT * FROM LokalnaBazaDanychTIN.dbo.Address WHERE LokalnaBazaDanychTIN.dbo.Address.id_client = ";
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sClientId));
	if (ExecutePreparedStatement(preparedStatement) == false) return vector;
	resultSet = preparedStatement->getResultSet();

	while (resultSet->next())
	{
		addressId = resultSet->getInt("id_address");
		name = resultSet->getString("addressee_name");
		value = resultSet->getString("address_name");
		vector.push_back(AddressModel(addressId, value, name));

	}

	return vector;
}

//IDAL.h
bool DAL::ChangeHashOfPassword(string login, string newHashOfPassword)
{
//	ResultSet *resultSet;
	PreparedStatement *preparedStatement;

	if (getClient(login).id < 0) return false;

	string part1 = "UPDATE LokalnaBazaDanychTIN.dbo.Client SET LokalnaBazaDanychTIN.dbo.Client.password_hash = '";
	string part2 = "' WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + newHashOfPassword + part2 + login + "'"));
	if (ExecutePreparedStatement(preparedStatement) == false) return false;

	return true;
}
bool DAL::BlockClient(string login)
{
////	ResultSet *resultSet;
	
	PreparedStatement *preparedStatement;

	if (getClient(login).id < 0) return false;

	string part1 = "UPDATE LokalnaBazaDanychTIN.dbo.Client SET LokalnaBazaDanychTIN.dbo.Client.blocked = 1 WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + login + "'"));
	if (ExecutePreparedStatement(preparedStatement) == false) return false;

	return true;
}
ClientModel DAL::getClient(string login)
{
	int clientId;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string hash;
	bool blocked;

	string part1 = "SELECT *  FROM  LokalnaBazaDanychTIN.dbo.Client WHERE login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + login  + "' "));
	if (ExecutePreparedStatement(preparedStatement) == false) return ClientModel(-1, "", "", false);
	resultSet = preparedStatement->getResultSet();

	if(resultSet->next() == false) return ClientModel(-1, "", "", false);;
		
	clientId = resultSet->getInt("id_client");
	hash = resultSet->getString("password_hash");
	blocked = resultSet->getBoolean("blocked");

	return  ClientModel(clientId, login, hash, blocked);
}