#pragma once
#include "Erasable.h"

//class Erasable;

class Gift : public Erasable
{
public:
//	Gift();
//	~Gift();
	void chooseGift() const;

    Gift(const sf::Texture&, const sf::Vector2f&);

private:

};