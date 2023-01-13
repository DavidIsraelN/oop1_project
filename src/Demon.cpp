#include "Objects/Demon.h"

Demon::Demon(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
	: MovingObj(texture, position, width, height) { }

void Demon::move(sf::Time deltaTime)
{

}