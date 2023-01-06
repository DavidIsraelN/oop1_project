#pragma once
#include "MovingObj.h"
//class MovingObj;

class Pacman : public MovingObj
{
public:
  Pacman(const sf::Texture&, const sf::Vector2f&, float, float);
	//~Pacman();

//	void move() override;
//	void collusion() override;

    
    Object* clone() const;

private:

};