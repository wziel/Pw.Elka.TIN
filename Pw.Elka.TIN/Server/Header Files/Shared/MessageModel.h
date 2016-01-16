#ifndef MESSAGE_MODEL
#define MESSAGE_MODEL

#include <string>

using namespace std;

/// Klasa reprezentujaca struktur� szablonu wiadomo�ci
class MessageModel
{
public:
	/// Konstruktor bezargumentowy
	MessageModel() {}
	/// Konstruktor przypisuj�cy wszystkie dane wiadomo�ci
	/// id - id szablonu wiadomo�ci
	/// title - nazwa wiadomo�ci
	/// content - tre�� wiadomo��i
	MessageModel(int id, string title, string content) : id(id), title(title), content(content) {}
	/// Konstruktor pomijaj�cy przypisanie tre�ci (w celu wypisania samych nazw wiadomo�ci)
	/// id - id wiadomo�ci
	/// title - nazwa wiadomo�ci
	MessageModel(int id, string title) : id(id), title(title) {}
	/// Destruktor
	~MessageModel() {}

	int id;
	string title;
	string content;
};

#endif


