#pragma once
#include "Gift.h"

class LifeGift : public Gift
{
public:
	LifeGift(const sf::Vector2f& position, float width, float height)
    : Gift(ResourceManager::Resource().getObjTexture(ObjIndex::GIFT), position, width, height) { }

};
