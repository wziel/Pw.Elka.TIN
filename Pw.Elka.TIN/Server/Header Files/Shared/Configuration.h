#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Configuration
{
public:
	static Configuration& getConfiguration()
	{
		try 
		{
			static Configuration configuration;
			return configuration;
		}
		catch (char const* tekst)
		{
			std::cout << tekst << std::endl;
			exit(1);
		}
	}
	int getMaxSession()
	{
		return maxSession;
	}
	string getServerSmtpName()
	{
		return serverSmtpName;
	}
	short getPortSmtp()
	{
		return portSmtp;
	}
	string getEncryptedSmtpLogin()
	{
		return encryptedSmtpLogin;
	}
	string getEncryptedSmtpPassword()
	{
		return encryptedSmtpPassword;
	}
	short getPortToListen()
	{
		return portToListen;
	}

private:
	Configuration()
	{
		ifstream confFile("server.conf");
		if (!confFile.is_open())
		{
			throw "Cannot open configuration file!";
		}
		string data;
		while (getline(confFile, data, ':'))
		{
			if (data == "maxSession")
			{
				getline(confFile, data);
				maxSession = atoi(data.c_str());
			}
			else if (data == "serverSmtpName")
			{
				getline(confFile, data);
				serverSmtpName = data;
			}
			else if (data == "portSmtp")
			{
				getline(confFile, data);
				portSmtp = atoi(data.c_str());
			}
			else if (data == "encryptedSmtpLogin")
			{
				getline(confFile, data);
				encryptedSmtpLogin = data;
			}
			else if (data == "encryptedSmtpPassword")
			{
				getline(confFile, data);
				encryptedSmtpPassword = data;
			}
			else if (data == "portToListen")
			{
				getline(confFile, data);
				portToListen = atoi(data.c_str());
			}
			else
			{
				confFile.close();
				throw "Errors in configuration file!";
			}
		}
		confFile.close();
	}
	Configuration(const Configuration &) {}
	~Configuration(){}

	/* Data for RootManager */
	int maxSession;

	/* Data for SmtpLayer */
	string serverSmtpName;
	short portSmtp;
	string encryptedSmtpLogin;
	string encryptedSmtpPassword;

	/* Data for SessionListener */
	short portToListen;
};


#endif