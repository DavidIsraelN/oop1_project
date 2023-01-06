#pragma once
#include "Erasable.h"

//class Erasable;

class Gift : public Erasable
{
public:
  Gift(const sf::Texture&, const sf::Vector2f&, float, float);
//	~Gift();
	void chooseGift() const;

    

private:

};