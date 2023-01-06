#include <iostream>
#include "Controller.h"

int main()
{
	sf::Font font;
	font.loadFromFile("Arial.ttf");
	auto pacman_game = Controller(font);
	pacman_game.run();

	return EXIT_SUCCESS;
}
