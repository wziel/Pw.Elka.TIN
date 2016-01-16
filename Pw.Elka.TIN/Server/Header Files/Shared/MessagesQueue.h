#ifndef MESSAGES_QUEUE
#define MESSAGES_QUEUE

#include "../Shared/SmtpMessage.h"
#include <mutex>
#include <condition_variable>
#include <deque>

using namespace std;

/// Klasa reprezentuj¹ca kolejkê wiadomoœci miêdzy w¹tkami obs³uguj¹cymi klientów a w¹tkiem smtp
class MessagesQueue
{
private:
	/// Mutex pilnuj¹cy dostêpu do kolejki
	mutex queueMutex;
	/// Zmienna warunkowa s³u¿¹ca do poinformowania w¹tku smtp zawieszonym w oczekiwaniu na pobranie wiadomoœci
	condition_variable emptyCondition;
	/// Kolejka zawieraj¹ca wiadomoœci
	deque<SmtpMessage> queue;
	/// Zmienna logiczna informuj¹ca czy kolejka jest pusta
	bool empty;
public:
	/// Metoda pobieraj¹ca wiadomoœæ z kolejki
	/// return - wiadomoœæ na pocz¹tku kolejki
	SmtpMessage Pop();
	/// Metoda wstawiaj¹ca wiadomoœæ do kolejki
	/// smtpMessage - wiadomoœæ do wstawienia na koniec kolejki
	void Push(SmtpMessage smtpMessage);
	/// Metoda koñcz¹ca dzia³anie kolejki
	void End();
	/// Konstruktor bezargumentow
	MessagesQueue() : empty(true) { }
	/// Destruktor
	~MessagesQueue();
};

#endif