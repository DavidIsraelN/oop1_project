#include "Objects/Door.h"

Door::Door(const sf::Vector2f& position, float width, float height)
    : Erasable(*ResourceManage::Resource()->getDoorT(), position, width, height) { }
