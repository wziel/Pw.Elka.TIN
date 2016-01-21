#ifndef SESSION_LISTENER
#define SESSION_LISTENER

#include "../../Interfaces/ISessionListener.h"
#include "../../Interfaces/IClientCreator.h"
#include "../../Shared/Configuration.h"
#include <WinSock2.h>
#include <stdlib.h>

/// Klasa zajmuj�ca si� nas�uchiwaniem na kolejne nawi�zywanie po��cze�.
class SessionListener :
	public ISessionListener
{
public:
	/// Konstruktor. Otrzymuje referencj� na obiekt klasy zajmuj�cej si� obs�ug� pod��czaj�cych si� klient�w.
	SessionListener(IClientCreator &clientCreator);
	///Destruktor
	~SessionListener();
	/// Metody z interfejsu ISessionListener


	/// Funkcja rozpoczynaj�ca dzia�anie obiektu SessionListener. Realizuje nas�uchiwanie na po��czenie oraz jego obs�ug�.
	void Start();
	/// Funkcja ko�cz�ca dzia�anie obiektu SessionListener.
	void End();
private:
	/// Wskazanie na obiekt klasy zajmuj�cy si� obs�ug� pod��czaj�cych si� klient�w
	IClientCreator *clientCreator;
	/// Port do nas�uchiwania
	short portToListen;
	/// Deskryptor gniazda przyjmuj�cego po��czenia
	int socketDescriptor;
	/// Deskryptor gniazda do kt�rego pod��czony b�dzie nowy klient
	int newClientSocketDescriptor;
	/// D�ugo�� struktury zawieraj�cej dane gniazda pod��czonego klienta
	int newClientAddressLenght = sizeof(sockaddr_in);
	/// Struktura w kt�rej przechowywane s� dane dotycz�ce gniazda na kt�rym jest nas�uchiwanie
	struct sockaddr_in addressStruct;
	/// Struktura w kt�rej przechowywane s� dane dotycz�ce gniazda pod��czonego klienta
	struct sockaddr_in newClientAddressStruct;
	/// Tablica zawieraj�ca eventy zg�aszane przez aplikacj� lub przez pod��czenie si� nowego klienta
	WSAEVENT wsaEvents[2];
	/// Zmienna, kt�ra b�dzie wskazywa�a, kt�ry z event�w zosta� wywo�any
	int eventSignaled;
};

#endif