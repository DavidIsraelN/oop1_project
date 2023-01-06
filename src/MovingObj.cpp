#include "Objects/MovingObj.h"

MovingObj::MovingObj(const sf::Texture& texture, const sf::Vector2f& position, float width, float height ,float scale)
	: Object(texture, position, width, height, scale) { }
