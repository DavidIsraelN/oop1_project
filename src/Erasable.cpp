#include "Objects/Erasable.h"

Erasable::Erasable(const sf::Texture& texture, const sf::Vector2f& position, float width, float height, float scale)
	: StaticObj(texture, position, width, height, scale) { }