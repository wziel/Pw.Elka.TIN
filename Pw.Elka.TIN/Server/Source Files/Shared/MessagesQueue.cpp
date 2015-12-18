#include "../../Header Files/Shared/MessagesQueue.h"


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
	SmtpMessage smtpMessage;
	unique_lock<mutex> lock(this->queueMutex);
	if(empty)
		this->emptyCondition.wait(lock);
	smtpMessage = this->queue.back();
	this->queue.pop_back();
	if (queue.empty())
		empty = true;
	return smtpMessage;
}

void MessagesQueue::End()
{
	unique_lock<mutex> lock(this->queueMutex);
	queue.clear();
	queue.push_front(SmtpMessage(true));
}