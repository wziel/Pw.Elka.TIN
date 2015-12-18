#ifndef MESSAGES_QUEUE
#define MESSAGES_QUEUE

#include "../Shared/SmtpMessage.h"
#include <mutex>
#include <condition_variable>
#include <deque>

using namespace std;

class MessagesQueue
{
private:
	mutex queueMutex;
	condition_variable emptyCondition;
	deque<SmtpMessage> queue;
	bool empty;
public:
	SmtpMessage Pop();
	void Push(SmtpMessage smtpMessage);
	void End();
	MessagesQueue() : empty(true) { }
	~MessagesQueue();
};

#endif