#include "Objects/Demon.h"

Demon::Demon(const sf::Vector2f& position, float width, float height)
    : MovingObj(ResourceManage::Resource()->getObjTexture(ObjIndex::DEMON), position, width, height) { }

//void Demon::move(sf::Time deltaTime)
//{
//
//}