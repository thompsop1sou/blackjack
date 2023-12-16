#include "Game.h"

int main()
{
	Game bj;

	bj.intro();

	while (!bj.finished())
	{
		system("cls"); // Clears the screen for Windows.
		bj.display();
		bj.input();
		bj.process();
	}

	system("cls"); // Clears the screen for Windows.
	bj.results();

	system("pause"); // Pauses the screen for Windows.\

	return 0;
}