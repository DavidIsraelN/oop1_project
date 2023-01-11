#include <iostream>
#include "Controller.h"

int main()
{
	auto pacman_game = Controller();
	pacman_game.run();

	return EXIT_SUCCESS;
}
