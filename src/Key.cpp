#include "Objects/Key.h"

Key::Key(const sf::Vector2f& position, float width, float height)
    : Erasable(ResourceManager::Resource()->getObjTexture(ObjIndex::KEY), position, width, height, 1.5) { }
