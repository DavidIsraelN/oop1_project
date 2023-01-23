#include "Objects/Demon.h"

Demon::Demon(const sf::Vector2f& position, float width, float height, float win_width, float win_height)
    : MovingObj(ResourceManager::Resource().getObjTexture(ObjIndex::DEMON), position, width, height, win_width, win_height) { }

void Demon::move(sf::Time deltaTime)
{

}