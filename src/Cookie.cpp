#include "Objects/Cookie.h"
#include "Objects/Object.h"

Cookie::Cookie(const sf::Vector2f& position, float width, float height)
    : Erasable(ResourceManager::Resource()->getObjTexture(ObjIndex::COOKIE), position, width, height, 2) { }
