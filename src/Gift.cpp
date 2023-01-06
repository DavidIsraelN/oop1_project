#include "Objects/Gift.h"

Gift::Gift(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
	: Erasable(texture, position, width, height, 1.5) { }
