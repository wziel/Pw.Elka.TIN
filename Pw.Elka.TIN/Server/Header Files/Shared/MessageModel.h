#ifndef MESSAGE_MODEL
#define MESSAGE_MODEL

#include <string>

using namespace std;

class MessageModel
{
public:
	MessageModel() {}
	MessageModel(int id, string title, string content) : id(id), title(title), content(content) {}
	~MessageModel() {}

	int id;
	string title;
	string content;
};

#endif

