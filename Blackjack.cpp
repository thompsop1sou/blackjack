#include "Game.h"

int main()
{
	Game bj;

	bj.intro();

	while (!bj.finished())
	{
		bj.display();
		bj.input();
		bj.process();
	}

	bj.results();

	return 0;
}