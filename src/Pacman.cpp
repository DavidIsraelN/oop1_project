#include "Objects/Pacman.h"

Pacman::Pacman(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
	: MovingObj(texture, position, width, height) { }