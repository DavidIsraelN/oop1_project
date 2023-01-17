#include "Objects/Demon.h"

Demon::Demon(const sf::Vector2f& position, float width, float height)
    : MovingObj(*ResourceManage::Resource()->getDemonT(), position, width, height) { }

//void Demon::move(sf::Time deltaTime)
//{
//
//}