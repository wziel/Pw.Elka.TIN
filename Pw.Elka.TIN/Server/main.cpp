
#include "Header Files\Components\RootManager\RootManager.h"

int main()
{
	RootManager rootManager;
	rootManager.Start();
	rootManager.End();
	std::cout << "Server ended. Press any key to continue...\n";
	getchar();
	getchar();
}