#pragma once
#include "../../Interfaces/ILayer.h"
#include <string>
#define _WINSOCKAPI_ 
#include <windows.h>

using namespace std;
/// Klasa reprezentuj�ca szyfrator do szyfrowania oraz deszyfrowania wychodz�cych i przychodz�cych wiadomo�ci
class Cipher :
	public ILayer
{
public:
	/// Konstruktor, jako argument przyjmuje referencj� na ni�sz� warstw� do kt�rej wysy�a i od kt�rej odbiera wiadomo�ci
	Cipher(ILayer &bottomLayer);
	/// Destruktor
	~Cipher();
	
	/// Metody z interfejsu ILayer

	/// Wysy�a wiadomo�� do ni�szej warstwy
	/// buffer - wska�nik na bufor zawieraj�cy wiadomo��
	/// size - wielko�� bufora wskazywanego przez buffer
	void Send(unsigned char* buffer, int size);

	/// Odbiera wiadomo�� z ni�szej warstwy
	/// buffer - referencja na wska�nik do bufora zapisania wiadomo�ci
	/// size - referencja na wielko�� bufora s�u��cego do zapisania wiadomo�ci
	void Receive(unsigned char* &buffer, int &size);
private:

	/// Wska�nik na ni�sz� warstw�
	ILayer *bottomLayer;

	/// S�owo kodowe
	const char keyCode[7] = "michal";
};

