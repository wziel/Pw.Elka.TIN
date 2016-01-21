#ifndef SESSION_LISTENER
#define SESSION_LISTENER

#include "../../Interfaces/ISessionListener.h"
#include "../../Interfaces/IClientCreator.h"
#include "../../Shared/Configuration.h"
#include <WinSock2.h>
#include <stdlib.h>

/// Klasa zajmuj¹ca siê nas³uchiwaniem na kolejne nawi¹zywanie po³¹czeñ.
class SessionListener :
	public ISessionListener
{
public:
	/// Konstruktor. Otrzymuje referencjê na obiekt klasy zajmuj¹cej siê obs³ug¹ pod³¹czaj¹cych siê klientów.
	SessionListener(IClientCreator &clientCreator);
	///Destruktor
	~SessionListener();
	/// Metody z interfejsu ISessionListener


	/// Funkcja rozpoczynaj¹ca dzia³anie obiektu SessionListener. Realizuje nas³uchiwanie na po³¹czenie oraz jego obs³ugê.
	void Start();
	/// Funkcja koñcz¹ca dzia³anie obiektu SessionListener.
	void End();
private:
	/// Wskazanie na obiekt klasy zajmuj¹cy siê obs³ug¹ pod³¹czaj¹cych siê klientów
	IClientCreator *clientCreator;
	/// Port do nas³uchiwania
	short portToListen;
	/// Deskryptor gniazda przyjmuj¹cego po³¹czenia
	int socketDescriptor;
	/// Deskryptor gniazda do którego pod³¹czony bêdzie nowy klient
	int newClientSocketDescriptor;
	/// D³ugoœæ struktury zawieraj¹cej dane gniazda pod³¹czonego klienta
	int newClientAddressLenght = sizeof(sockaddr_in);
	/// Struktura w której przechowywane s¹ dane dotycz¹ce gniazda na którym jest nas³uchiwanie
	struct sockaddr_in addressStruct;
	/// Struktura w której przechowywane s¹ dane dotycz¹ce gniazda pod³¹czonego klienta
	struct sockaddr_in newClientAddressStruct;
	/// Tablica zawieraj¹ca eventy zg³aszane przez aplikacjê lub przez pod³¹czenie siê nowego klienta
	WSAEVENT wsaEvents[2];
	/// Zmienna, która bêdzie wskazywa³a, który z eventów zosta³ wywo³any
	int eventSignaled;
};

#endif