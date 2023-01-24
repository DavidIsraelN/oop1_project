#pragma once
#include "Gift.h"

class SuperPGift : public Gift
{
public:
	SuperPGift(const sf::Vector2f& position, float width, float height)
		: Gift(ResourceManager::Resource().getObjTexture(ObjIndex::GIFT), position, width, height) { }

};
