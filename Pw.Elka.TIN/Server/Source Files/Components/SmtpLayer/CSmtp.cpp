#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "../../../Header Files/Components/SmtpLayer/SmtpLayer.h"
#include <Ws2tcpip.h>


/// DESCRIPTION: Constructor of CSmtp class.
///     RETURNS: none
CSmtp::CSmtp()
{
	m_iXPriority = XPRIORITY_NORMAL;
	m_iSMTPSrvPort = 0;

	/// Initialize WinSock
	WSADATA wsaData;
	WORD wVer = MAKEWORD(2,2);    
	if (WSAStartup(wVer,&wsaData) != NO_ERROR)
		throw ECSmtp(ECSmtp::WSA_STARTUP);
	if (LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 ) 
	{
		WSACleanup();
		throw ECSmtp(ECSmtp::WSA_VER);
	}
	
	if((RecvBuf = new char[BUFFER_SIZE]) == NULL)
		throw ECSmtp(ECSmtp::LACK_OF_MEMORY);
	
	if((SendBuf = new char[BUFFER_SIZE]) == NULL)
		throw ECSmtp(ECSmtp::LACK_OF_MEMORY);
}


/// DESCRIPTION: Destructor of CSmtp class.
///  RETURNS: none
CSmtp::~CSmtp()
{
	if(SendBuf)
	{
		delete[] SendBuf;
		SendBuf = NULL;
	}
	if(RecvBuf)
	{
		delete[] RecvBuf;
		RecvBuf = NULL;
	}


	WSACleanup();
}


/// DESCRIPTION: New recipient data is added i.e.: email and name. .
///   ARGUMENTS: const char *email - mail of the recipient
///              const char *name - name of the recipient
///     RETURNS: void
void CSmtp::AddRecipient(const char *email, const char *name)
{	
	if(!email)
		throw ECSmtp(ECSmtp::UNDEF_RECIPIENT_MAIL);

	Recipient recipient;
	recipient.Mail.insert(0,email);
	name!=NULL ? recipient.Name.insert(0,name) : recipient.Name.insert(0,"");

	Recipients.insert(Recipients.end(), recipient);   
}



/// DESCRIPTION: Adds new line in a message.
///   ARGUMENTS: const char *Text - text of the new line
///     RETURNS: void
void CSmtp::AddMsgLine(const char* Text)
{
	MsgBody.insert(MsgBody.end(),Text);
}

/// DESCRIPTION: Deletes specified line in text message.. .
///   ARGUMENTS: unsigned int Line - line to be delete
///     RETURNS: void
void CSmtp::DelMsgLine(unsigned int Line)
{
	if(Line > MsgBody.size())
		throw ECSmtp(ECSmtp::OUT_OF_MSG_RANGE);
	MsgBody.erase(MsgBody.begin()+Line);
}

/// DESCRIPTION: Deletes all recipients. .
///     RETURNS: void
void CSmtp::DelRecipients()
{
	Recipients.clear();
}


/// DESCRIPTION: Deletes message text.
///   ARGUMENTS: void
void CSmtp::DelMsgLines()
{
	MsgBody.clear();
}


/// DESCRIPTION: New recipient data is added i.e.: email and name. .
///  ARGUMENTS: const char *email - mail of the bcc-recipient
///              const char *name - name of the bccc-recipient
///    RETURNS: void

void CSmtp::ModMsgLine(unsigned int Line,const char* Text)
{
	if(Text)
	{
		if(Line > MsgBody.size())
			throw ECSmtp(ECSmtp::OUT_OF_MSG_RANGE);
		MsgBody.at(Line) = std::string(Text);
	}
}

/// DESCRIPTION: Sending the mail.
///   ARGUMENTS: none
///     RETURNS: void
void CSmtp::Send()
{
	unsigned int i, rcpt_count;
	char *FileBuf = NULL, *FileName = NULL;
	FILE* hFile = NULL;
//	unsigned long int FileSize,TotalSize,MsgPart;
	bool bAccepted;

	// ***** CONNECTING TO SMTP SERVER *****

	// connecting to remote host:
	if( (hSocket = ConnectRemoteServer(m_sSMTPSrvName.c_str(), m_iSMTPSrvPort)) == INVALID_SOCKET ) 
		throw ECSmtp(ECSmtp::WSA_INVALID_SOCKET);

	bAccepted = false;
	do
	{
		ReceiveData();
		switch(SmtpXYZdigits())
		{
			case 220:
				bAccepted = true;
				break;
			default:
				throw ECSmtp(ECSmtp::SERVER_NOT_READY);
		}
	}while(!bAccepted);

	// EHLO <SP> <domain> <CRLF>
	sprintf(SendBuf,"EHLO %s\r\n",GetLocalHostName()!=NULL ? m_sLocalHostName.c_str() : "domain");
	SendData();
	bAccepted = false;
	do
	{
		ReceiveData();
		switch(SmtpXYZdigits())
		{
			case 250:
				bAccepted = true;
				break;
			default:
				throw ECSmtp(ECSmtp::COMMAND_EHLO);
		}
	}while(!bAccepted);

	// AUTH <SP> LOGIN <CRLF>
	strcpy(SendBuf,"AUTH LOGIN\r\n");
	SendData();
	bAccepted = false;
	do
	{
		ReceiveData();
		switch(SmtpXYZdigits())
		{
			case 250:
				break;
			case 334:
				//std::cout << "czeka na login";
				bAccepted = true;
				break;
			default:
				throw ECSmtp(ECSmtp::COMMAND_AUTH_LOGIN);
		}
	}while(!bAccepted);

	// send login:
	if(!m_sLogin.size())
		throw ECSmtp(ECSmtp::UNDEF_LOGIN);
	sprintf(SendBuf,"%s\r\n", this->m_sLogin);
	SendData();
	bAccepted = false;
	do
	{
		ReceiveData();
		switch(SmtpXYZdigits())
		{
			case 334:
				bAccepted = true;
				break;
			default:
				throw ECSmtp(ECSmtp::UNDEF_XYZ_RESPONSE);
		}
	}while(!bAccepted);
	
	// send password:
	if(!m_sPassword.size())
		throw ECSmtp(ECSmtp::UNDEF_PASSWORD);
	sprintf(SendBuf,"%s\r\n", this->m_sPassword );
	SendData();
	bAccepted = false;
	do
	{
		ReceiveData();
		switch(SmtpXYZdigits())
		{
			case 235:
				bAccepted = true;
				break;
			case 334:
				break;
			case 535:
				throw ECSmtp(ECSmtp::BAD_LOGIN_PASS);
			default:
				throw ECSmtp(ECSmtp::UNDEF_XYZ_RESPONSE);
		}
	}while(!bAccepted);

	//  SENDING E-MAIL 
	
	// MAIL <SP> FROM:<reverse-path> <CRLF>
	if(!m_sMailFrom.size())
		throw ECSmtp(ECSmtp::UNDEF_MAIL_FROM);
	sprintf(SendBuf,"MAIL FROM:<%s>\r\n",m_sMailFrom.c_str());
	SendData();
	bAccepted = false;
	do
	{
		ReceiveData();
		switch(SmtpXYZdigits())
		{
			case 250:
				bAccepted = true;
				break;
			default:
				throw ECSmtp(ECSmtp::COMMAND_MAIL_FROM);
		}
	}while(!bAccepted);

	// RCPT <SP> TO:<forward-path> <CRLF>
	if(!(rcpt_count = Recipients.size()))
		throw ECSmtp(ECSmtp::UNDEF_RECIPIENTS);
	for(i=0;i<Recipients.size();i++)
	{
		sprintf(SendBuf,"RCPT TO:<%s>\r\n",(Recipients.at(i).Mail).c_str());
		SendData();
		bAccepted = false;
		do
		{
			ReceiveData();
			switch(SmtpXYZdigits())
			{
				case 250:
					bAccepted = true;
					break;
				default:
					rcpt_count--;
			}
		}while(!bAccepted);
	}
	if(rcpt_count <= 0)
		throw ECSmtp(ECSmtp::COMMAND_RCPT_TO);


	
	// DATA <CRLF>
	strcpy(SendBuf,"DATA\r\n");
	SendData();
	bAccepted = false;
	do
	{
		ReceiveData();
		switch(SmtpXYZdigits())
		{
			case 354:
				bAccepted = true;
				break;
			case 250:
				break;
			default:
				throw ECSmtp(ECSmtp::COMMAND_DATA);
		}
	}while(!bAccepted);
	
	// send header(s)
	FormatHeader(SendBuf);
	SendData();

	// send text message
	if(GetMsgLines())
	{
		for(i=0;i<GetMsgLines();i++)
		{
			sprintf(SendBuf,"%s\r\n",GetMsgLineText(i));
			SendData();
		}
	}
	else
	{
		sprintf(SendBuf,"%s\r\n"," ");
		SendData();
	}

	
	// <CRLF> . <CRLF>
	strcpy(SendBuf,"\r\n.\r\n");
	SendData();
	bAccepted = false;
	do
	{
		ReceiveData();
		switch(SmtpXYZdigits())
		{
			case 250:
				bAccepted = true;
				break;
			default:
				throw ECSmtp(ECSmtp::MSG_BODY_ERROR);
		}
	}while(!bAccepted);

	// ***** CLOSING CONNECTION *****
	
	// QUIT <CRLF>
	strcpy(SendBuf,"QUIT\r\n");
	SendData();
	bAccepted = false;
	do
	{
		ReceiveData();
		switch(SmtpXYZdigits())
		{
			case 221:
				bAccepted = true;
				break;
			default:
				throw ECSmtp(ECSmtp::COMMAND_QUIT);
		}
	}while(!bAccepted);


	closesocket(hSocket);

	hSocket = NULL;
	std::cout << "Message succesfully sent. \n";
}


/// DESCRIPTION: Connecting to the service running on the remote server. 
///   ARGUMENTS: const char *server - service name
///              const unsigned short port - service port
///     RETURNS: socket of the remote service
SOCKET CSmtp::ConnectRemoteServer(const char *szServer,const unsigned short nPort_)
{
	unsigned short nPort = 0;
	LPSERVENT lpServEnt;
	SOCKADDR_IN sockAddr;
	unsigned long ul = 1;
	fd_set fdwrite,fdexcept;
	timeval timeout;
	int res = 0;

	timeout.tv_sec = TIME_IN_SEC;
	timeout.tv_usec = 0;

	SOCKET hSocket = INVALID_SOCKET;

	if((hSocket = socket(PF_INET, SOCK_STREAM,0)) == INVALID_SOCKET)
		throw ECSmtp(ECSmtp::WSA_INVALID_SOCKET);

	if(nPort_ != 0)
		nPort = htons(nPort_);
	else
	{
		lpServEnt = getservbyname("mail", 0);
		if (lpServEnt == NULL)
			nPort = htons(25);
		else 
			nPort = lpServEnt->s_port;
	}
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = nPort;
	//inet_pton(AF_INET, szServer , &sockAddr.sin_addr.s_addr); alternatywnie
	//if(( sockAddr.sin_addr.s_addr ) == INADDR_NONE)
		if ((sockAddr.sin_addr.s_addr = inet_addr(szServer)) == INADDR_NONE)
	{
		LPHOSTENT host;
		
		host = gethostbyname(szServer);
		if (host)
		{
	
			memcpy(&sockAddr.sin_addr, host->h_addr_list[0], host->h_length);
		}
		else
		{

			closesocket(hSocket);
			throw ECSmtp(ECSmtp::WSA_GETHOSTBY_NAME_ADDR);
		}				
	}

	// start non-blocking mode for socket:

	if(ioctlsocket(hSocket,FIONBIO, (unsigned long*)&ul) == SOCKET_ERROR)

	{

		closesocket(hSocket);

		throw ECSmtp(ECSmtp::WSA_IOCTLSOCKET);
	}

	if(connect(hSocket,(LPSOCKADDR)&sockAddr,sizeof(sockAddr)) == SOCKET_ERROR)
	{
		if(WSAGetLastError() != WSAEWOULDBLOCK)

		{
			closesocket(hSocket);

			throw ECSmtp(ECSmtp::WSA_CONNECT);
		}
	}
	else
		return hSocket;

	while(true)
	{
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdexcept);

		FD_SET(hSocket,&fdwrite);
		FD_SET(hSocket,&fdexcept);

		if((res = select(hSocket+1,NULL,&fdwrite,&fdexcept,&timeout)) == SOCKET_ERROR)
		{

			closesocket(hSocket);

			throw ECSmtp(ECSmtp::WSA_SELECT);
		}

		if(!res)
		{

			closesocket(hSocket);

			throw ECSmtp(ECSmtp::SELECT_TIMEOUT);
		}
		if(res && FD_ISSET(hSocket,&fdwrite))
			break;
		if(res && FD_ISSET(hSocket,&fdexcept))
		{

			closesocket(hSocket);

			throw ECSmtp(ECSmtp::WSA_SELECT);
		}
	} // while

	FD_CLR(hSocket,&fdwrite);
	FD_CLR(hSocket,&fdexcept);

	return hSocket;
}

/// DESCRIPTION: Converts three letters from RecvBuf to the number.
///   ARGUMENTS: none
///     RETURNS: integer number
int CSmtp::SmtpXYZdigits()
{
	assert(RecvBuf);
	if(RecvBuf == NULL)
		return 0;
	return (RecvBuf[0]-'0')*100 + (RecvBuf[1]-'0')*10 + RecvBuf[2]-'0';
}


/// DESCRIPTION: Prepares a header of the message.
///   ARGUMENTS: char* header - formated header string
///     RETURNS: void
void CSmtp::FormatHeader(char* header)
{
	char month[][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	size_t i;
	std::string to;
	std::string cc;
	
	time_t rawtime;
	struct tm* timeinfo;

	// date/time check
	if(time(&rawtime) > 0)
		timeinfo = localtime(&rawtime);
	else
		throw ECSmtp(ECSmtp::TIME_ERROR);

	// check for at least one recipient
	if(Recipients.size())
	{
		for (i=0;i<Recipients.size();i++)
		{
			if(i > 0)
				to.append(",");
			to += Recipients[i].Name;
			to.append("<");
			to += Recipients[i].Mail;
			to.append(">");
		}
	}
	else
		throw ECSmtp(ECSmtp::UNDEF_RECIPIENTS);


	
	// Date: <SP> <dd> <SP> <mon> <SP> <yy> <SP> <hh> ":" <mm> ":" <ss> <SP> <zone> <CRLF>
	sprintf(header,"Date: %d %s %d %d:%d:%d\r\n",	timeinfo->tm_mday,
																								month[timeinfo->tm_mon],
																								timeinfo->tm_year+1900,
																								timeinfo->tm_hour,
																								timeinfo->tm_min,
																								timeinfo->tm_sec); 
	
	// From: <SP> <sender>  <SP> "<" <sender-email> ">" <CRLF>
	if(!m_sMailFrom.size())
		throw ECSmtp(ECSmtp::UNDEF_MAIL_FROM);
	strcat(header,"From: ");
	if(m_sNameFrom.size())
		strcat(header, m_sNameFrom.c_str());
	strcat(header," <");
	if(m_sNameFrom.size())
		strcat(header,m_sMailFrom.c_str());
	else
		strcat(header,"mail@domain.com");
	strcat(header, ">\r\n");

	// X-Mailer: <SP> <xmailer-app> <CRLF>
	if(m_sXMailer.size())
	{
		strcat(header,"X-Mailer: ");
		strcat(header, m_sXMailer.c_str());
		strcat(header, "\r\n");
	}

	// Reply-To: <SP> <reverse-path> <CRLF>
	if(m_sReplyTo.size())
	{
		strcat(header, "Reply-To: ");
		strcat(header, m_sReplyTo.c_str());
		strcat(header, "\r\n");
	}

	// X-Priority: <SP> <number> <CRLF>
	switch(m_iXPriority)
	{
		case XPRIORITY_HIGH:
			strcat(header,"X-Priority: 2 (High)\r\n");
			break;
		case XPRIORITY_NORMAL:
			strcat(header,"X-Priority: 3 (Normal)\r\n");
			break;
		case XPRIORITY_LOW:
			strcat(header,"X-Priority: 4 (Low)\r\n");
			break;
		default:
			strcat(header,"X-Priority: 3 (Normal)\r\n");
	}

	// To: <SP> <remote-user-mail> <CRLF>
	strcat(header,"To: ");
	strcat(header, to.c_str());
	strcat(header, "\r\n");


	// Subject: <SP> <subject-text> <CRLF>
	if(!m_sSubject.size()) 
		strcat(header, "Subject:  ");
	else
	{
	  strcat(header, "Subject: ");
	  strcat(header, m_sSubject.c_str());
	}
	strcat(header, "\r\n");
	

}


/// DESCRIPTION: Receives a row terminated '\n'.
///   ARGUMENTS: none
///     RETURNS: void
void CSmtp::ReceiveData()
{
	int res,i = 0;
	fd_set fdread;
	timeval time;

	time.tv_sec = TIME_IN_SEC;
	time.tv_usec = 0;

	assert(RecvBuf);

	if(RecvBuf == NULL)
		throw ECSmtp(ECSmtp::RECVBUF_IS_EMPTY);

	while(1)
	{
		FD_ZERO(&fdread);

		FD_SET(hSocket,&fdread);

		if((res = select(hSocket+1, &fdread, NULL, NULL, &time)) == SOCKET_ERROR)
		{
			FD_CLR(hSocket,&fdread);
			throw ECSmtp(ECSmtp::WSA_SELECT);
		}

		if(!res)
		{
			//timeout
			FD_CLR(hSocket,&fdread);
			throw ECSmtp(ECSmtp::SERVER_NOT_RESPONDING);
		}

		if(res && FD_ISSET(hSocket,&fdread))
		{
			if(i >= BUFFER_SIZE)
			{
				FD_CLR(hSocket,&fdread);
				throw ECSmtp(ECSmtp::LACK_OF_MEMORY);
			}
			if(recv(hSocket,&RecvBuf[i++],1,0) == SOCKET_ERROR)
			{
				FD_CLR(hSocket,&fdread);
				throw ECSmtp(ECSmtp::WSA_RECV);
			}
			if(RecvBuf[i-1]=='\n')
			{
				RecvBuf[i] = '\0';
				break;
			}
		}
	}

	FD_CLR(hSocket,&fdread);
}

/// DESCRIPTION: Sends data from SendBuf buffer.
///   ARGUMENTS: none
///     RETURNS: void
void CSmtp::SendData()
{
	int idx = 0,res,nLeft = strlen(SendBuf);
	fd_set fdwrite;
	timeval time;

	time.tv_sec = TIME_IN_SEC;
	time.tv_usec = 0;

	assert(SendBuf);

	if(SendBuf == NULL)
		throw ECSmtp(ECSmtp::SENDBUF_IS_EMPTY);

	while(1)
	{
		FD_ZERO(&fdwrite);

		FD_SET(hSocket,&fdwrite);

		if((res = select(hSocket+1,NULL,&fdwrite,NULL,&time)) == SOCKET_ERROR)
		{
			FD_CLR(hSocket,&fdwrite);
			throw ECSmtp(ECSmtp::WSA_SELECT);
		}

		if(!res)
		{
			//timeout
			FD_CLR(hSocket,&fdwrite);
			throw ECSmtp(ECSmtp::SERVER_NOT_RESPONDING);
		}

		if(res && FD_ISSET(hSocket,&fdwrite))
		{
			if(nLeft > 0)
			{
				if((res = send(hSocket,&SendBuf[idx],nLeft,0)) == SOCKET_ERROR)
				{
					FD_CLR(hSocket,&fdwrite);
					throw ECSmtp(ECSmtp::WSA_SEND);
				}
				if(!res)
					break;
				nLeft -= res;
				idx += res;
			}
			else
				break;
		}
	}

	FD_CLR(hSocket,&fdwrite);
}

/// DESCRIPTION: Returns local host name. 
///   ARGUMENTS: none
///     RETURNS: socket of the remote service
const char* CSmtp::GetLocalHostName() const
{
	char* str = NULL;

	if((str = new char[255]) == NULL)
		throw ECSmtp(ECSmtp::LACK_OF_MEMORY);
	if(gethostname(str,255) == SOCKET_ERROR)
	{
		delete[] str;
		throw ECSmtp(ECSmtp::WSA_HOSTNAME);
	}
	delete[] str;
	return m_sLocalHostName.c_str();
}


/// DESCRIPTION: Returns the number of recipents.
///   ARGUMENTS: none
///     RETURNS: number of recipents
unsigned int CSmtp::GetRecipientCount() const
{
	return Recipients.size();
}


/// DESCRIPTION: Returns m_pcReplyTo string.
///   ARGUMENTS: none
///     RETURNS: m_sReplyTo string
const char* CSmtp::GetReplyTo() const
{
	return m_sReplyTo.c_str();
}


/// DESCRIPTION: Returns m_pcMailFrom string.
///   ARGUMENTS: none
///     RETURNS: m_sMailFrom string
const char* CSmtp::GetMailFrom() const
{
	return m_sMailFrom.c_str();
}


/// DESCRIPTION: Returns m_pcNameFrom string.
///   ARGUMENTS: none
///     RETURNS: m_sNameFrom string
const char* CSmtp::GetSenderName() const
{
	return m_sNameFrom.c_str();
}


/// DESCRIPTION: Returns m_pcSubject string.
///   ARGUMENTS: none
///     RETURNS: m_sSubject string
const char* CSmtp::GetSubject() const
{
	return m_sSubject.c_str();
}


/// DESCRIPTION: Returns m_pcXMailer string.
///   ARGUMENTS: none
///     RETURNS: m_pcXMailer string
const char* CSmtp::GetXMailer() const
{
	return m_sXMailer.c_str();
}


/// DESCRIPTION: Returns m_iXPriority string.
///   ARGUMENTS: none
///     RETURNS: CSmptXPriority m_pcXMailer
CSmptXPriority CSmtp::GetXPriority() const
{
	return m_iXPriority;
}

const char* CSmtp::GetMsgLineText(unsigned int Line) const
{
	if(Line > MsgBody.size())
		throw ECSmtp(ECSmtp::OUT_OF_MSG_RANGE);
	return MsgBody.at(Line).c_str();
}

unsigned int CSmtp::GetMsgLines() const
{
	return MsgBody.size();
}


/// DESCRIPTION: Setting priority of the message.
///   ARGUMENTS: CSmptXPriority priority - priority of the message (	XPRIORITY_HIGH,
///              XPRIORITY_NORMAL, XPRIORITY_LOW)
///     RETURNS: none
void CSmtp::SetXPriority(CSmptXPriority priority)
{
	m_iXPriority = priority;
}


/// DESCRIPTION: Setting the return address.
///   ARGUMENTS: const char *ReplyTo - return address
///     RETURNS: none
void CSmtp::SetReplyTo(const char *ReplyTo)
{
	m_sReplyTo.erase();
	m_sReplyTo.insert(0,ReplyTo);
}


/// DESCRIPTION: Setting sender's mail.
///   ARGUMENTS: const char *EMail - sender's e-mail
///     RETURNS: none
void CSmtp::SetSenderMail(const char *EMail)
{
	m_sMailFrom.erase();
	m_sMailFrom.insert(0,EMail);
}


/// DESCRIPTION: Setting sender's name.
///   ARGUMENTS: const char *Name - sender's name
///     RETURNS: none
void CSmtp::SetSenderName(const char *Name)
{
	m_sNameFrom.erase();
	m_sNameFrom.insert(0,Name);
}


/// DESCRIPTION: Setting subject of the message.
///   ARGUMENTS: const char *Subject - subject of the message
///     RETURNS: none
void CSmtp::SetSubject(const char *Subject)
{
	m_sSubject.erase();
	m_sSubject.insert(0,Subject);
}


/// DESCRIPTION: Setting the name of program which is sending the mail.
///   ARGUMENTS: const char *XMailer - programe name
///     RETURNS: none
void CSmtp::SetXMailer(const char *XMailer)
{
	m_sXMailer.erase();
	m_sXMailer.insert(0,XMailer);
}


/// DESCRIPTION: Setting the login of SMTP account's owner.
///   ARGUMENTS: const char *Login - login of SMTP account's owner
///     RETURNS: none
void CSmtp::SetLogin(const char *Login)
{
	m_sLogin.erase();
	m_sLogin.insert(0,Login);
}


/// DESCRIPTION: Setting the password of SMTP account's owner.
///   ARGUMENTS: const char *Password - password of SMTP account's owner
///     RETURNS: none
void CSmtp::SetPassword(const char *Password)
{
	m_sPassword.erase();
	m_sPassword.insert(0,Password);
}


/// DESCRIPTION: Setting the SMTP service name and port.
///   ARGUMENTS: const char* SrvName - SMTP service name
///              const unsigned short SrvPort - SMTO service port
///     RETURNS: none
void CSmtp::SetSMTPServer(const char* SrvName,const unsigned short SrvPort)
{
	m_iSMTPSrvPort = SrvPort;
	m_sSMTPSrvName.erase();
	m_sSMTPSrvName.insert(0,SrvName);
}

/// DESCRIPTION: Returns the string for specified error code.
///   ARGUMENTS: CSmtpError ErrorId - error code
///     RETURNS: error string
std::string ECSmtp::GetErrorText() const
{
	switch(ErrorCode)
	{
		case ECSmtp::CSMTP_NO_ERROR:
			return "";
		case ECSmtp::WSA_STARTUP:
			return "Unable to initialise winsock2";
		case ECSmtp::WSA_VER:
			return "Wrong version of the winsock2";
		case ECSmtp::WSA_SEND:
			return "Function send() failed";
		case ECSmtp::WSA_RECV:
			return "Function recv() failed";
		case ECSmtp::WSA_CONNECT:
			return "Function connect failed";
		case ECSmtp::WSA_GETHOSTBY_NAME_ADDR:
			return "Unable to determine remote server";
		case ECSmtp::WSA_INVALID_SOCKET:
			return "Invalid winsock2 socket";
		case ECSmtp::WSA_HOSTNAME:
			return "Function hostname() failed";
		case ECSmtp::WSA_IOCTLSOCKET:
			return "Function ioctlsocket() failed";
		case ECSmtp::BAD_IPV4_ADDR:
			return "Improper IPv4 address";
		case ECSmtp::UNDEF_MSG_HEADER:
			return "Undefined message header";
		case ECSmtp::UNDEF_MAIL_FROM:
			return "Undefined mail sender";
		case ECSmtp::UNDEF_SUBJECT:
			return "Undefined message subject";
		case ECSmtp::UNDEF_RECIPIENTS:
			return "Undefined at least one reciepent";
		case ECSmtp::UNDEF_RECIPIENT_MAIL:
			return "Undefined recipent mail";
		case ECSmtp::UNDEF_LOGIN:
			return "Undefined user login";
		case ECSmtp::UNDEF_PASSWORD:
			return "Undefined user password";
		case ECSmtp::COMMAND_MAIL_FROM:
			return "Server returned error after sending MAIL FROM";
		case ECSmtp::COMMAND_EHLO:
			return "Server returned error after sending EHLO";
		case ECSmtp::COMMAND_AUTH_LOGIN:
			return "Server returned error after sending AUTH LOGIN";
		case ECSmtp::COMMAND_DATA:
			return "Server returned error after sending DATA";
		case ECSmtp::COMMAND_QUIT:
			return "Server returned error after sending QUIT";
		case ECSmtp::COMMAND_RCPT_TO:
			return "Server returned error after sending RCPT TO";
		case ECSmtp::MSG_BODY_ERROR:
			return "Error in message body";
		case ECSmtp::CONNECTION_CLOSED:
			return "Server has closed the connection";
		case ECSmtp::SERVER_NOT_READY:
			return "Server is not ready";
		case ECSmtp::SERVER_NOT_RESPONDING:
			return "Server not responding";
		case ECSmtp::FILE_NOT_EXIST:
			return "File not exist";
		case ECSmtp::MSG_TOO_BIG:
			return "Message is too big";
		case ECSmtp::BAD_LOGIN_PASS:
			return "Bad login or password";
		case ECSmtp::UNDEF_XYZ_RESPONSE:
			return "Undefined xyz SMTP response";
		case ECSmtp::LACK_OF_MEMORY:
			return "Lack of memory";
		case ECSmtp::TIME_ERROR:
			return "time() error";
		case ECSmtp::RECVBUF_IS_EMPTY:
			return "RecvBuf is empty";
		case ECSmtp::SENDBUF_IS_EMPTY:
			return "SendBuf is empty";
		case ECSmtp::OUT_OF_MSG_RANGE:
			return "Specified line number is out of message size";
		default:
			return "Undefined error id";
	}
}

