#pragma once

class Communicate
{
public:

	Communicate();
	Communicate(char* communicateBuffer);
	~Communicate();

	//Returns code of communicate
	unsigned char getCode();
	//returns communicate size
	int getSize();
	//returns communicate content
	char* getCommunicate();


protected:
//Communicate content
	char* communicateBuffer;
//Communicate size
	int size;
};

