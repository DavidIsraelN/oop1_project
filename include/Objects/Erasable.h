#pragma once
#include "StaticObj.h"
#include "Pacman.h"

//abstract class

class Erasable : public StaticObj
{
public:
  Erasable(const sf::Texture&, const sf::Vector2f&, float, float, float = 1);
  bool isDel() const { return m_obj_del; }
  void delObj() { m_obj_del = true; }

private:
  bool m_obj_del = false;
};
