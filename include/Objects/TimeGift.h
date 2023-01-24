#pragma once
#include "Gift.h"

class TimeGift : public Gift
{
public:
	TimeGift(const sf::Vector2f& position, float width, float height)
		: Gift(ResourceManager::Resource().getObjTexture(ObjIndex::GIFT), position, width, height) { }

};
