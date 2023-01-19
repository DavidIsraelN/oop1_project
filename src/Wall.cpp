#include "Objects/Wall.h"

Wall::Wall(const sf::Vector2f& position, float width, float height)
    : StaticObj(ResourceManage::Resource()->getObjTexture(ObjIndex::WALL), position, width, height) { }
