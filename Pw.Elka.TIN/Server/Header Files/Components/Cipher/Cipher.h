#pragma once
#include "../../Interfaces/ILayer.h"
#include <string>
#define _WINSOCKAPI_ 
#include <windows.h>

using namespace std;
/// Klasa reprezentuj¹ca szyfrator do szyfrowania oraz deszyfrowania wychodz¹cych i przychodz¹cych wiadomoœci
class Cipher :
	public ILayer
{
public:
	/// Konstruktor, jako argument przyjmuje referencjê na ni¿sz¹ warstwê do której wysy³a i od której odbiera wiadomoœci
	Cipher(ILayer &bottomLayer);
	/// Destruktor
	~Cipher();
	
	/// Metody z interfejsu ILayer

	/// Wysy³a wiadomoœæ do ni¿szej warstwy
	/// buffer - wskaŸnik na bufor zawieraj¹cy wiadomoœæ
	/// size - wielkoœæ bufora wskazywanego przez buffer
	void Send(unsigned char* buffer, int size);

	/// Odbiera wiadomoœæ z ni¿szej warstwy
	/// buffer - referencja na wskaŸnik do bufora zapisania wiadomoœci
	/// size - referencja na wielkoœæ bufora s³u¿¹cego do zapisania wiadomoœci
	void Receive(unsigned char* &buffer, int &size);
private:

	/// WskaŸnik na ni¿sz¹ warstwê
	ILayer *bottomLayer;

	/// S³owo kodowe
	const char keyCode[7] = "michal";
};

