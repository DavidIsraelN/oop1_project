#pragma once
#pragma once
#include "Gift.h"

class FreezeGift : public Gift
{
public:
	FreezeGift(const sf::Vector2f& position, float width, float height)
		: Gift(ResourceManager::Resource().getObjTexture(ObjIndex::GIFT), position, width, height) { }

};
