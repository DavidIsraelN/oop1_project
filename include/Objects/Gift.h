#pragma once
#include "Erasable.h"

class Gift : public Erasable
{
public:
  Gift(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
    : Erasable(texture, position, width, height, 1.5) { }
//  virtual ~Gift() = 0;
//  void chooseGift() const;

};
