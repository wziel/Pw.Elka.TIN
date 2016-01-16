#ifndef MESSAGE_MODEL
#define MESSAGE_MODEL

#include <string>

using namespace std;

/// Klasa reprezentujaca strukturê szablonu wiadomoœci
class MessageModel
{
public:
	/// Konstruktor bezargumentowy
	MessageModel() {}
	/// Konstruktor przypisuj¹cy wszystkie dane wiadomoœci
	/// id - id szablonu wiadomoœci
	/// title - nazwa wiadomoœci
	/// content - treœæ wiadomoœæi
	MessageModel(int id, string title, string content) : id(id), title(title), content(content) {}
	/// Konstruktor pomijaj¹cy przypisanie treœci (w celu wypisania samych nazw wiadomoœci)
	/// id - id wiadomoœci
	/// title - nazwa wiadomoœci
	MessageModel(int id, string title) : id(id), title(title) {}
	/// Destruktor
	~MessageModel() {}

	int id;
	string title;
	string content;
};

#endif


