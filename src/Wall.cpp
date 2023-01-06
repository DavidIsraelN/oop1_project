#include "Objects/Wall.h"

Wall::Wall(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
	: StaticObj(texture, position, width, height) { }
