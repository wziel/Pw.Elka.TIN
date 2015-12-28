#pragma once

class Communicate
{
public:

	Communicate();
	Communicate(char* communicateBuffer);
	~Communicate();

	//Returns code of communicate
	unsigned char getCode();

private:
//Communicate
	char* communicateBuffer;

};

