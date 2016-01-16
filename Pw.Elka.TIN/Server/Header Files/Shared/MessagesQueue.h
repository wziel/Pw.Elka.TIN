#ifndef MESSAGES_QUEUE
#define MESSAGES_QUEUE

#include "../Shared/SmtpMessage.h"
#include <mutex>
#include <condition_variable>
#include <deque>

using namespace std;

/// Klasa reprezentuj�ca kolejk� wiadomo�ci mi�dzy w�tkami obs�uguj�cymi klient�w a w�tkiem smtp
class MessagesQueue
{
private:
	/// Mutex pilnuj�cy dost�pu do kolejki
	mutex queueMutex;
	/// Zmienna warunkowa s�u��ca do poinformowania w�tku smtp zawieszonym w oczekiwaniu na pobranie wiadomo�ci
	condition_variable emptyCondition;
	/// Kolejka zawieraj�ca wiadomo�ci
	deque<SmtpMessage> queue;
	/// Zmienna logiczna informuj�ca czy kolejka jest pusta
	bool empty;
public:
	/// Metoda pobieraj�ca wiadomo�� z kolejki
	/// return - wiadomo�� na pocz�tku kolejki
	SmtpMessage Pop();
	/// Metoda wstawiaj�ca wiadomo�� do kolejki
	/// smtpMessage - wiadomo�� do wstawienia na koniec kolejki
	void Push(SmtpMessage smtpMessage);
	/// Metoda ko�cz�ca dzia�anie kolejki
	void End();
	/// Konstruktor bezargumentow
	MessagesQueue() : empty(true) { }
	/// Destruktor
	~MessagesQueue();
};

#endif