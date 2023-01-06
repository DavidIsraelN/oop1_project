#pragma once
#include "StaticObj.h"

//class StaticObj;

//abstract class

class Erasable : public StaticObj
{
public:
	Erasable(const sf::Texture&, const sf::Vector2f&, float, float, float = 1);
  //virtual ~Erasable() = 0;
	bool isDel();

private:
	bool m_obj_del = false;
};
