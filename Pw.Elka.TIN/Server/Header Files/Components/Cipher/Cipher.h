#pragma once
#include "../../Interfaces/ILayer.h"
#include <string>
#define _WINSOCKAPI_ 
#include <windows.h>

using namespace std;

class Cipher :
	public ILayer
{
public:
	Cipher(ILayer &bottomLayer);
	~Cipher();
	//ILayer
	void Send(char* buffer, int size);
	void Receive(char* buffer, int &size);
private:
	ILayer *bottomLayer;
	const char keyCode[7] = "michal";
};

