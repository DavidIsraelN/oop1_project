#include "Objects/Door.h"

Door::Door(const sf::Vector2f& position, float width, float height)
    : Erasable(ResourceManager::Resource()->getObjTexture(ObjIndex::DOOR), position, width, height) { }
