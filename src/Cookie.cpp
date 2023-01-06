#include "Objects/Cookie.h"
#include "Objects/Object.h"

Cookie::Cookie(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
: Erasable(texture, position, width, height, 2) { }
