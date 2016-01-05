#pragma once
#define _CLICOMAUTH			  0x00
#define _CLICOMMSGCREATE	  0x02
#define _CLICOMMSGMODIFY	  0x03
#define _CLICOMMSGDELETE	  0x04
#define _CLICOMMSGGETALL	  0x05
#define _CLICOMMSGGETONE	  0x06
#define _CLICOMGRPCREATE	  0x07
#define _CLICOMGRPDELETE	  0x08
#define _CLICOMGRPGETONE	  0x09
#define _CLICOMGRPGETALL	  0x0A
#define _CLICOMGRPADRADD	  0x0B
#define _CLICOMGRPADRRMV	  0x0C
#define _CLICOMSEND			  0x0D
#define _CLICOMPSSWCHG		  0x0E
#define _CLICOMADDRADD		  0x18
#define _CLICOMADDRRMV		  0x19
#define _CLICOMADDRGETALL	  0x1A
#define _SERVCOMAUTH		  0x00
#define _SERVCOMACK			  0x01
#define _SERVCOMMSGGETALL	  0x05
#define _SERVCOMMSGGETONE	  0x06
#define _SERVCOMGRPGETONE	  0x09
#define _SERVCOMGRPGETALL	  0x0A
#define _SERVCOMERRUNAUTH	  0x0F
#define _SERVCOMERRBUSY		  0x10
#define _SERVCOMERRLOGIN	  0x11
#define _SERVCOMERRBADREQ     0x12
#define _SERVCOMERRBADCONTENT 0x13
#define _SERVCOMERRGROUP	  0x14
#define _SERVCOMERRMSG		  0x15
#define _SERVCOMERRSERVUNAV	  0x16
#define _SERVCOMADDRGETONE	  0x17
#define _SERVCOMADDRGETALL    0x1A
#define _SERVCOMERRADDR		  0x1B

#include <string> 

class Communicate
{
public:

	Communicate();
	Communicate(unsigned char* communicateBuffer);
	~Communicate();

	//Returns code of communicate
	unsigned char getCode();
	//returns communicate size
	int getSize();
	//returns communicate content
	unsigned char* getCommunicate();


protected:
//Communicate content
	unsigned char* communicateBuffer;
//Communicate size
	int size;
};

