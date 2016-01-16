#include "../../Header Files/Shared/MessagesQueue.h"
#include <iostream>

MessagesQueue::~MessagesQueue()
{

}

void MessagesQueue::Push(const SmtpMessage smtpMessage)
{
	unique_lock<mutex> lock(this->queueMutex);
	queue.push_front(smtpMessage);
	if (empty)
	{
		empty = false;
		this->emptyCondition.notify_one();
	}
}

SmtpMessage MessagesQueue::Pop()
{
	unique_lock<mutex> lock(this->queueMutex);
	if(empty)
		this->emptyCondition.wait(lock);
	SmtpMessage smtpMessage = this->queue.back();
	this->queue.pop_back();
	if (queue.empty())
		empty = true;
	return smtpMessage;
}

void MessagesQueue::End()
{
	unique_lock<mutex> lock(this->queueMutex);
	queue.clear();
	vector<string> s;
	queue.push_front(SmtpMessage(true));
}