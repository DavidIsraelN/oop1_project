#pragma once
#include "Object.h"

//abstract class

class StaticObj : public Object
{
public:
  StaticObj(const sf::Texture&, const sf::Vector2f&, float, float, float = 1);
  //virtual ~StaticObj() = 0;
};
