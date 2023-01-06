#include "Objects/Door.h"

Door::Door(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
	: Erasable(texture, position, width, height) { }
