#include "game/Game.h"

int main()
{
	// Game beginning
	Game bj;
	bj.intro();

	// Game loop
	while (!bj.finished())
	{
		bj.display();
		bj.input();
		bj.process();
	}

	// Game end
	bj.results();

	return 0;
}