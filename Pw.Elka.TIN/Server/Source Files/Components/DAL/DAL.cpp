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

//IAdminDAL.h
bool DAL::BlockClient(string login, bool isBlocked)
{

	PreparedStatement *preparedStatement;

	string part1 = "UPDATE LokalnaBazaDanychTIN.dbo.Client SET LokalnaBazaDanychTIN.dbo.Client.blocked = 1 WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + login + "'"));
	preparedStatement->execute();
	//return 0;
	return true;
}
bool DAL::CreateClient(string login, string hashOfPassword)
{
	int clientId;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;

	string part1 = "INSERT INTO LokalnaBazaDanychTIN.dbo.Client ( login, password_hash , blocked ) VALUES( '";
	string part2 = " Select IDENT_CURRENT( 'LokalnaBazaDanychTIN.dbo.Client' ) AS last_inserted_row ";


	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + login + "' , '" + hashOfPassword + "' ,  0  )"));
	preparedStatement->execute();

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part2));
	preparedStatement->execute();

	resultSet = preparedStatement->getResultSet();
	resultSet->next();

	clientId = resultSet->getInt("last_inserted_row");
	//return 0;
	return true;
}
bool DAL::DeleteClient(string login)
{

	PreparedStatement *preparedStatement;
	string  sClientId, sMessageId;

	//DELETE FROM LokalnaBazaDanychTIN.dbo.Message
	//WHERE LokalnaBazaDanychTIN.dbo.Message.id_message = 12

	string part1 = "DELETE FROM LokalnaBazaDanychTIN.dbo.Client WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + login + "'"));
	preparedStatement->execute();

	//return 0;

	return true;
}
bool DAL::ChangeLogin(string login, string newLogin)
{

	PreparedStatement *preparedStatement;

	string part1 = "UPDATE LokalnaBazaDanychTIN.dbo.Client SET LokalnaBazaDanychTIN.dbo.Client.login = '";
	string part2 = "' WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + newLogin + part2 + login + "'"));
	preparedStatement->execute();

	//return  0;

	return true;
}
vector<ClientModel> DAL::GetAllClients()
{
	int clientId;
	string login, hash;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	vector<ClientModel>  vector;

	//SELECT * FROM LokalnaBazaDanychTIN.dbo.Address
	//WHERE LokalnaBazaDanychTIN.dbo.Address.id_client = 2


	string part1 = "SELECT * FROM LokalnaBazaDanychTIN.dbo.Client ";
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1));
	preparedStatement->execute();
	resultSet = preparedStatement->getResultSet();

	while (resultSet->next())
	{
		clientId = resultSet->getInt("id_client");
		login = resultSet->getString("login");
		hash = resultSet->getString("password_hash");
		vector.push_back(ClientModel(clientId, login, hash));

	}

	//cout << "message id;  " << messageId << endl;
	//cout << "temat:  " << title << endl;
	//cout << "zawartosc: " << content << endl; 


	return  vector;


	/* MOCK 

	vector<ClientModel> klienci;

	ClientModel klient1(1, "Michal", "hashHasla");
	ClientModel klient2(2, "Asia", "hashHasla");
	ClientModel klient3(3, "Wojtek", "hashHasla");

	klienci.push_back(klient1);
	klienci.push_back(klient2);
	klienci.push_back(klient3);

	return klienci;*/
}

bool  DAL::UnblockClient(string login)
{

	PreparedStatement *preparedStatement;

	string part1 = "UPDATE LokalnaBazaDanychTIN.dbo.Client SET LokalnaBazaDanychTIN.dbo.Client.blocked = 0 WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + login + "'"));
	preparedStatement->execute();
	
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
	preparedStatement->execute();
	resultSet = preparedStatement->getResultSet();
	resultSet->next();
	//cout << "Column (Id): " << r->getInt("id_message") << endl;
	//cout << "Column (Id): " << r->getInt("id_client") << endl;
	//cout << "Column (_message): " << r->getString("title") << endl;
	//cout << "Column (_message): " << r->getString("content") << endl;
	title = resultSet->getString("title");
	content = resultSet->getString("content");

	//cout << "message id;  " << mssageId << endl;
	//cout << "temat:  " << title << endl;
	//cout << "zawartosc: " << content << endl;


	return  MessageModel(mssageId, title, content);

	/* MOCK 

	MessageModel wiadomosc1(8, "Wiadomosc1", "To jest bardzo superowa wiadomosc, ktora mozna sobie wyslac lub tez nie. Albo lepiej komus a nie sobie");
	return wiadomosc1;*/
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
	preparedStatement->execute();


	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part2));
	preparedStatement->execute();

	resultSet = preparedStatement->getResultSet();
	resultSet->next();

	messageId = resultSet->getInt("last_inserted_row");
	//cout << "message id;  " << messageId << endl;
	//cout << "temat:  " << title << endl;
	//cout << "zawartosc: " << content << endl; 


	return  MessageModel(messageId, title, content);
	/* MOCK 

	MessageModel wiadomosc1(8, "Wiadomosc1", "");
	return wiadomosc1;*/
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

	//UPDATE LokalnaBazaDanychTIN.dbo.Message
	//SET LokalnaBazaDanychTIN.dbo.Message.title = 'mozna czy nie',
	//LokalnaBazaDanychTIN.dbo.Message.content = 'tak sie zastanawialem',
	//LokalnaBazaDanychTIN.dbo.Message.id_client = '2'
	//WHERE LokalnaBazaDanychTIN.dbo.Message.id_message = 21

	string part1 = "UPDATE LokalnaBazaDanychTIN.dbo.Message SET LokalnaBazaDanychTIN.dbo.Message.title = '";
	string part2 = "', LokalnaBazaDanychTIN.dbo.Message.content = '";
	string part3 = "', LokalnaBazaDanychTIN.dbo.Message.id_client = '";
	string part4 = "' WHERE LokalnaBazaDanychTIN.dbo.Message.id_message = ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + title + part2 + content + part3 + sClientId + part4 + sMessageId));
	preparedStatement->execute();

	//resultSet = preparedStatement->getResultSet();
	//resultSet->next();

	//messageId = resultSet->getInt("last_inserted_row");
	//cout << "message id;  " << messageId << endl;
	//cout << "temat:  " << title << endl;
	//cout << "zawartosc: " << content << endl; 


	return  MessageModel(messageId, title, content);
	/* MOCK 

	MessageModel wiadomosc1(8, title, content);
	return wiadomosc1; */
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

	//DELETE FROM LokalnaBazaDanychTIN.dbo.Message
	//WHERE LokalnaBazaDanychTIN.dbo.Message.id_message = 12

	string part1 = "DELETE FROM LokalnaBazaDanychTIN.dbo.Message WHERE LokalnaBazaDanychTIN.dbo.Message.id_message = ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sMessageId));
	preparedStatement->execute();

	//resultSet = preparedStatement->getResultSet();
	//resultSet->next();

	//messageId = resultSet->getInt("last_inserted_row");
	//cout << "message id;  " << messageId << endl;
	//cout << "temat:  " << title << endl;
	//cout << "zawartosc: " << content << endl; 

	return 0;

	/* MOCK 

	return true;*/
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


	//SELECT LokalnaBazaDanychTIN.dbo.Message.id_message, LokalnaBazaDanychTIN.dbo.Message.title
	//	FROM LokalnaBazaDanychTIN.dbo.Message
	//	WHERE LokalnaBazaDanychTIN.dbo.Message.id_client = 2


	string part1 = "SELECT LokalnaBazaDanychTIN.dbo.Message.id_message, LokalnaBazaDanychTIN.dbo.Message.title FROM LokalnaBazaDanychTIN.dbo.Message WHERE LokalnaBazaDanychTIN.dbo.Message.id_client = ";
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sClientId));
	preparedStatement->execute();
	resultSet = preparedStatement->getResultSet();

	while (resultSet->next())
	{
		messageId = resultSet->getInt("id_message");
		title = resultSet->getString("title");
		vector.push_back(MessageModel(messageId, title));

	}

	//cout << "message id;  " << messageId << endl;
	//cout << "temat:  " << title << endl;
	//cout << "zawartosc: " << content << endl; 


	return  vector;
	/* MOCK 

	MessageModel wiadomosc1(1, "Wiadomosc1", "");
	MessageModel wiadomosc2(2, "Wiadomosc2", "");
	MessageModel wiadomosc3(3, "Wiadomosc3", "");

	vector<MessageModel> wiadomosci;
	wiadomosci.push_back(wiadomosc1);
	wiadomosci.push_back(wiadomosc2);
	wiadomosci.push_back(wiadomosc3);

	return wiadomosci;*/
}
//--------------NIEPRZETESTOWANE-------------------------------------------
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

	// SELECT * FROM LokalnaBazaDanychTIN.dbo.[Group] WHERE LokalnaBazaDanychTIN.dbo.[Group].id_client = 
	string part1 = " SELECT * FROM LokalnaBazaDanychTIN.dbo.[Group] WHERE LokalnaBazaDanychTIN.dbo.[Group].id_client = ";
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sClientId));
	preparedStatement->execute();
	resultSet = preparedStatement->getResultSet();

	while (resultSet->next())
	{
		groupId = resultSet->getInt("id_group");
		nameOfGroup = resultSet->getString("name");
		groups.push_back(GroupModel(groupId, nameOfGroup));
	}
	return  groups;
	/* MOCK 

	vector<AddressModel> adresy;

	GroupModel grupa1(1, "Grupa1", adresy);
	GroupModel grupa2(2, "Grupa2", adresy);
	GroupModel grupa3(3, "Grupa3", adresy);

	vector<GroupModel> grupy;
	grupy.push_back(grupa1);
	grupy.push_back(grupa2);
	grupy.push_back(grupa3);

	return grupy;*/
}
GroupModel DAL::GetGroupById(int groupId, int clientId)
{



	//Select  *  From LokalnaBazaDanychTIN.dbo.Group_Address
	//	JOIN LokalnaBazaDanychTIN.dbo.Address
	//	ON LokalnaBazaDanychTIN.dbo.Group_Address.id_address = LokalnaBazaDanychTIN.dbo.Address.id_address
	//	Where LokalnaBazaDanychTIN.dbo.Group_Address.id_group = 9
	//id name adresses

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
	preparedStatement->execute();
	resultSet = preparedStatement->getResultSet();

	while (resultSet->next())
	{
		addressId = resultSet->getInt("id_address");
		addresseeName = resultSet->getString("addressee_name");
		value = resultSet->getString("address_name");

		addresses.push_back(AddressModel(addressId, value, addresseeName));
	}
	//--------------NIEPRZETESTOWANE-------------------------------------------
	string part2 = " SELECT LokalnaBazaDanychTIN.dbo.[Group].name FROM LokalnaBazaDanychTIN.dbo.[Group] WHERE LokalnaBazaDanychTIN.dbo.[Group].id_group = ";
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part2 + sGroupId));
	preparedStatement->execute();
	resultSet = preparedStatement->getResultSet();
	resultSet->next();
	nameOfGroup = resultSet->getString("name");

	return  GroupModel(groupId, nameOfGroup, addresses);

	/* MOCK 

	vector<AddressModel> adresy;

	AddressModel adres1(1, "michal@gmail.com", "Michal");
	AddressModel adres2(2, "asia@gmail.com", "Asia");
	AddressModel adres3(3, "wojtek@gmail.com", "Wojtek");

	adresy.push_back(adres1);
	adresy.push_back(adres2);
	adresy.push_back(adres3);

	GroupModel grupa1(1, "Grupa1", adresy);

	return grupa1;*/
}
//--------------NIEPRZETESTOWANE-------------------------------------------
bool DAL::DeleteGroupById(int groupId, int clientId)
{
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sGroupId;
	ostringstream konwersja;
	konwersja << groupId;
	sGroupId = konwersja.str();
	konwersja.str("");
	konwersja.clear();


	//DELETE FROM LokalnaBazaDanychTIN.dbo.[Group]
	//WHERE LokalnaBazaDanychTIN.dbo.[Group].id_group = 12

	string part1 = "DELETE FROM LokalnaBazaDanychTIN.dbo.[Group] WHERE LokalnaBazaDanychTIN.dbo.[Group].id_group = ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sGroupId));
	preparedStatement->execute();

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


	//	INSERT INTO LokalnaBazaDanychTIN.dbo.[Group]( id_client , name ) VALUES('6', 'Grupa dbra')

	//	Select IDENT_CURRENT('LokalnaBazaDanychTIN.dbo.[Group]') AS last_inserted_row


	string part1 = " INSERT INTO LokalnaBazaDanychTIN.dbo.[Group]( id_client , name ) VALUES( ";
	string part2 = "Select IDENT_CURRENT('LokalnaBazaDanychTIN.dbo.[Group]') AS last_inserted_row";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sClientId + " , '" + name + "' )"));
	preparedStatement->execute();

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part2));
	preparedStatement->execute();

	resultSet = preparedStatement->getResultSet();
	resultSet->next();
	groupId = resultSet->getInt("last_inserted_row");

	return GroupModel(groupId, name);
	/* MOCK 

	vector<AddressModel> adresy;
	GroupModel grupa1(8, "Grupa1", adresy);

	return grupa1; */
}
bool DAL::AddAddressToGroup(int groupId, int addressId, int clientId)
{
	//INSERT INTO LokalnaBazaDanychTIN.dbo.Group_Address(id_group, id_address) VALUES(5, 1)

	ResultSet *resultSet;
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
	preparedStatement->execute();

	//cout << "message id;  " << messageId << endl;
	//cout << "temat:  " << title << endl;
	//cout << "zawartosc: " << content << endl; 



	return true;
}
bool DAL::RemoveAddressFromGroup(int groupId, int addressId, int clientId)
{
	ResultSet *resultSet;
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
	preparedStatement->execute();


	return true;
}
string DAL::GetHashOfPassword(string username)
{

	string hash;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;


	string part1 = "SELECT LokalnaBazaDanychTIN.dbo.Client.password_hash  FROM  LokalnaBazaDanychTIN.dbo.Client WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";
	//string part2 = " AND  id_message = ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + username + " ' "));
	preparedStatement->execute();
	resultSet = preparedStatement->getResultSet();
	resultSet->next();

	hash = resultSet->getString("password_hash");

	return  hash;
	/* MOCK

	return string("test"); */
}
bool DAL::IsBlocked(int clientId)
{

	bool option;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;

	string part1 = "SELECT LokalnaBazaDanychTIN.dbo.Client.blocked  FROM  LokalnaBazaDanychTIN.dbo.Client WHERE LokalnaBazaDanychTIN.dbo.Client.id_client = ";
	string  sClientId;
	ostringstream konwersja;
	konwersja << clientId;
	sClientId = konwersja.str();
	konwersja.str("");
	konwersja.clear();

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sClientId));
	preparedStatement->execute();
	resultSet = preparedStatement->getResultSet();
	resultSet->next();

	option = resultSet->getInt("blocked");

	return  option;
	/* MOCK 

	return false;
	*/
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


	//INSERT INTO LokalnaBazaDanychTIN.dbo.Address(addressee_name, address_name) VALUES('Miko?aj', 'mikolaj@pedzio.com')

	//	Select IDENT_CURRENT('LokalnaBazaDanychTIN.dbo.Address') AS last_inserted_row


	string part1 = "INSERT INTO LokalnaBazaDanychTIN.dbo.Address(addressee_name, address_name , id_client) VALUES('";
	string part2 = "Select IDENT_CURRENT('LokalnaBazaDanychTIN.dbo.Address') AS last_inserted_row";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + addrName + "' , '" + addrValue + "', " + sClientId + " )"));
	preparedStatement->execute();

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part2));
	preparedStatement->execute();

	resultSet = preparedStatement->getResultSet();
	resultSet->next();
	messageId = resultSet->getInt("last_inserted_row");

	return AddressModel(messageId, addrValue, addrName);
	/* MOCK 

	return *new AddressModel(8,addrValue, addrName);*/
}
bool DAL::DeleteAddress(int addrId, int clientId)
{
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string  sAddrId, sClientId;
	ostringstream konwersja;
	konwersja << addrId;
	sAddrId = konwersja.str();
	konwersja.str("");
	konwersja.clear();
	konwersja << addrId;
	sAddrId = konwersja.str();

	//DELETE FROM LokalnaBazaDanychTIN.dbo.Message
	//WHERE LokalnaBazaDanychTIN.dbo.Message.id_message = 12

	string part1 = "DELETE FROM LokalnaBazaDanychTIN.dbo.Address WHERE LokalnaBazaDanychTIN.dbo.Address.id_address = ";
	//string part2 = ", LokalnaBazaDanychTIN.dbo.Message.id_client =  ";
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sAddrId));
	preparedStatement->execute();

	//resultSet = preparedStatement->getResultSet();
	//resultSet->next();

	//messageId = resultSet->getInt("last_inserted_row");
	//cout << "message id;  " << messageId << endl;
	//cout << "temat:  " << title << endl;
	//cout << "zawartosc: " << content << endl; 

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


	//SELECT * FROM LokalnaBazaDanychTIN.dbo.Address
	//WHERE LokalnaBazaDanychTIN.dbo.Address.id_client = 2


	string part1 = "SELECT * FROM LokalnaBazaDanychTIN.dbo.Address WHERE LokalnaBazaDanychTIN.dbo.Address.id_client = ";
	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + sClientId));
	preparedStatement->execute();
	resultSet = preparedStatement->getResultSet();

	while (resultSet->next())
	{
		addressId = resultSet->getInt("id_address");
		name = resultSet->getString("addressee_name");
		value = resultSet->getString("address_name");
		vector.push_back(AddressModel(addressId, value, name));

	}

	return vector;

	/* MOCK 

	AddressModel adres1(1, "michal@gmail.com", "Michal");
	AddressModel adres2(2, "asia@gmail.com", "Asia");
	AddressModel adres3(3, "wojtek@gmail.com", "Wojtek");

	vector<AddressModel> adresy;
	adresy.push_back(adres1);
	adresy.push_back(adres2);
	adresy.push_back(adres3);

	return adresy;*/
}

//IDAL.h
bool DAL::ChangeHashOfPassword(string login, string newHashOfPassword)
{
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;

	string part1 = "UPDATE LokalnaBazaDanychTIN.dbo.Client SET LokalnaBazaDanychTIN.dbo.Client.password_hash = '";
	string part2 = "' WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + newHashOfPassword + part2 + login + "'"));
	preparedStatement->execute();

	return true;
}
bool DAL::BlockClient(string login)
{
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;

	string part1 = "UPDATE LokalnaBazaDanychTIN.dbo.Client SET LokalnaBazaDanychTIN.dbo.Client.blocked = 1 WHERE LokalnaBazaDanychTIN.dbo.Client.login = '";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + login + "'"));
	preparedStatement->execute();

	return true;
}
ClientModel DAL::getClient(string login)
{
	int clientId;
	ResultSet *resultSet;
	PreparedStatement *preparedStatement;
	string hash;

	string part1 = "SELECT *  FROM  LokalnaBazaDanychTIN.dbo.Client WHERE login = '";
	string part2 = "' ";

	preparedStatement = connection->prepareStatement(ODBCXX_STRING_CONST(part1 + login + part2));
	preparedStatement->execute();
	resultSet = preparedStatement->getResultSet();
	resultSet->next();
	clientId = resultSet->getInt("id_client");
	hash = resultSet->getString("password_hash");

	return  ClientModel(clientId, login, hash);
	/* MOCK 
	//hashOfPassword is a hash used in application when inserted password 'test' 

	string str("û2ö \xf");
	str.append(1, '\0');
	str.append("7û#à'\xf\x11!ü#");

	return *(new ClientModel(1, login, str));*/
}
//
//
//DAL::DAL()
//{
//}
//
//
//DAL::~DAL()
//{
//}
//
////IAdminDAL.h
//bool DAL::BlockClient(string login, bool isBlocked)
//{
//	/* MOCK */
//
//	return true;
//}
//bool DAL::CreateClient(string login, string hashOfPassword)
//{
//	/* MOCK */
//
//	return true;
//}
//bool DAL::DeleteClient(string login)
//{
//	/* MOCK */
//
//	return true;
//}
//bool DAL::ChangeLogin(string login, string newLogin)
//{
//	/* MOCK */
//
//	return true;
//}
//vector<ClientModel> DAL::GetAllClients()
//{
//	/* MOCK */
//
//	vector<ClientModel> klienci;
//
//	ClientModel klient1(1, "Michal", "hashHasla");
//	ClientModel klient2(2, "Asia", "hashHasla");
//	ClientModel klient3(3, "Wojtek", "hashHasla");
//
//	klienci.push_back(klient1);
//	klienci.push_back(klient2);
//	klienci.push_back(klient3);
//
//	return klienci;
//}
//
//bool  DAL::UnblockClient(string login)
//{
//	/* MOCK */
//
//	return true;
//}
//
////IClientDAL.h
//MessageModel DAL::GetMessageById(int id, int clientId)
//{
//	/* MOCK */
//
//	MessageModel wiadomosc1(8, "Wiadomosc1", "To jest bardzo superowa wiadomosc, ktora mozna sobie wyslac lub tez nie. Albo lepiej komus a nie sobie");
//	return wiadomosc1;
//}
//MessageModel DAL::CreateMessage(string title, string content, int clientId)
//{
//	/* MOCK */
//
//	MessageModel wiadomosc1(8, "Wiadomosc1", "");
//	return wiadomosc1;
//}
//MessageModel DAL::ModifyMessage(int id, string title, string content, int clientId)
//{
//	/* MOCK */
//
//	MessageModel wiadomosc1(8, title, content);
//	return wiadomosc1;
//}
//bool DAL::DeleteMessage(int id, int clientId)
//{
//	/* MOCK */
//
//	return true;
//}
//vector<MessageModel> DAL::GetAllMessagesWithoutContent(int clientId)
//{
//	/* MOCK */
//
//	MessageModel wiadomosc1(1, "Wiadomosc1", "");
//	MessageModel wiadomosc2(2, "Wiadomosc2", "");
//	MessageModel wiadomosc3(3, "Wiadomosc3", "");
//
//	vector<MessageModel> wiadomosci;
//	wiadomosci.push_back(wiadomosc1);
//	wiadomosci.push_back(wiadomosc2);
//	wiadomosci.push_back(wiadomosc3);
//
//	return wiadomosci;
//}
//vector<GroupModel> DAL::GetAllGroupsWithoutAdresses(int clientId)
//{
//	/* MOCK */
//
//	vector<AddressModel> adresy;
//
//	GroupModel grupa1(1, "Grupa1", adresy);
//	GroupModel grupa2(2, "Grupa2", adresy);
//	GroupModel grupa3(3, "Grupa3", adresy);
//
//	vector<GroupModel> grupy;
//	grupy.push_back(grupa1);
//	grupy.push_back(grupa2);
//	grupy.push_back(grupa3);
//
//	return grupy;
//}
//GroupModel DAL::GetGroupById(int id, int clientId)
//{
//	/* MOCK */
//
//	vector<AddressModel> adresy;
//
//	AddressModel adres1(1, "michal@gmail.com", "Michal");
//	AddressModel adres2(2, "asia@gmail.com", "Asia");
//	AddressModel adres3(3, "wojtek@gmail.com", "Wojtek");
//
//	adresy.push_back(adres1);
//	adresy.push_back(adres2);
//	adresy.push_back(adres3);
//
//	GroupModel grupa1(1, "Grupa1", adresy);
//
//	return grupa1;
//}
//bool DAL::DeleteGroupById(int id, int clientId)
//{
//	/* MOCK */
//
//	return true;
//}
//GroupModel DAL::CreateGroup(string name, int clientId)
//{
//	/* MOCK */
//
//	vector<AddressModel> adresy;
//	GroupModel grupa1(8, "Grupa1", adresy);
//
//	return grupa1;
//}
//bool DAL::AddAddressToGroup(int groupId, int addressId, int clientId)
//{
//	/* MOCK */
//
//	return true;
//}
//bool DAL::RemoveAddressFromGroup(int groupId, int addressId, int clientId)
//{
//	/* MOCK */
//
//	return true;
//}
//string DAL::GetHashOfPassword(string username)
//{
//	/* MOCK */
//
//	return string("test");
//}
//bool DAL::IsBlocked(int clientId)
//{
//	/* MOCK */
//
//	return false;
//}
//AddressModel DAL::CreateAddress(string addrName, string addrValue, int clientId)
//{
//	/* MOCK */
//
//	return *new AddressModel(8, addrValue, addrName);
//}
//bool DAL::DeleteAddress(int addrId, int clientId)
//{
//	/* MOCK */
//
//	return true;
//}
//vector<AddressModel> DAL::GetAllAddresses(int clientId)
//{
//
//	/* MOCK */
//
//	AddressModel adres1(1, "michal@gmail.com", "Michal");
//	AddressModel adres2(2, "asia@gmail.com", "Asia");
//	AddressModel adres3(3, "wojtek@gmail.com", "Wojtek");
//
//	vector<AddressModel> adresy;
//	adresy.push_back(adres1);
//	adresy.push_back(adres2);
//	adresy.push_back(adres3);
//
//	return adresy;
//}
//
////IDAL.h
//bool DAL::ChangeHashOfPassword(string login, string newHashOfPassword)
//{
//	/* MOCK */
//
//	return true;
//}
//bool DAL::BlockClient(string login)
//{
//	/* MOCK */
//
//	return true;
//}
//ClientModel DAL::getClient(string login)
//{
//	/* MOCK */
//	//hashOfPassword is a hash used in application when inserted password 'test' 
//
//	string str("û2ö \xf");
//	str.append(1, '\0');
//	str.append("7û#à'\xf\x11!ü#");
//
//	return *(new ClientModel(1, login, str));
//}