#pragma once
#include "Object.h"

//abstract class

class MovingObj : public Object
{
public:
	MovingObj(const sf::Texture&, const sf::Vector2f&, float, float, float = 1);
//	virtual void move() = 0;
//	virtual void collusion() = 0;
};
