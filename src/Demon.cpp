#include "Objects/Demon.h"
#include "Level.h"

Demon::Demon(const sf::Vector2f& position, float width, float height)
    : MovingObj(ResourceManager::Resource().getObjTexture(ObjIndex::DEMON), position, width, height) { }

void Demon::move(const sf::Time& deltaTime, const Level& level, float win_height, float win_width)
{

}