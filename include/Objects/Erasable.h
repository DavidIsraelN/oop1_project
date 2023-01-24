#pragma once
#include "StaticObj.h"
#include "Sound.h"

//abstract class
class Erasable : public StaticObj
{
public:
  Erasable(const sf::Texture& texture, const sf::Vector2f& position,
    float width, float height, float scale = 1)
    : StaticObj(texture, position, width, height, scale) { }

//  virtual ~Erasable()  { } = 0;
  bool isDel() const { return m_obj_del; }
  void delObj() { m_obj_del = true; }

private:
  bool m_obj_del = false;
};
