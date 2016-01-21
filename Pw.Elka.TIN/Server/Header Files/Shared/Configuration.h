#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Configuration
{
public:
	static void initialize()
	{
		ifstream confFile(filename);
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
	static int getMaxSession()
	{
		return maxSession;
	}
	static string getServerSmtpName()
	{
		return serverSmtpName;
	}
	static short getPortSmtp()
	{
		return portSmtp;
	}
	static string getEncryptedSmtpLogin()
	{
		return encryptedSmtpLogin;
	}
	static string getEncryptedSmtpPassword()
	{
		return encryptedSmtpPassword;
	}
	static short getPortToListen()
	{
		return portToListen;
	}

	static string filename;
private:

	/* Data for RootManager */
	static int maxSession;

	/* Data for SmtpLayer */
	static string serverSmtpName;
	static short portSmtp;
	static string encryptedSmtpLogin;
	static string encryptedSmtpPassword;

	/* Data for SessionListener */
	static short portToListen;
};


#endif