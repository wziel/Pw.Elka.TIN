#include "../../Header Files/Shared/Configuration.h"

int Configuration::maxSession = 0;
string Configuration::serverSmtpName = "";
short Configuration::portSmtp = 0;
string Configuration::encryptedSmtpLogin = "";
string Configuration::encryptedSmtpPassword = "";
short Configuration::portToListen = 0;
string Configuration::filename = "server.conf";