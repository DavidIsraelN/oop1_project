#pragma once
#include "MovingObj.h"
//class MovingObj;

class Pacman : public MovingObj
{
public:
//	Pacman();
	//~Pacman();

//	void move() override;
//	void collusion() override;

    Pacman(const sf::Texture&, const sf::Vector2f&);
    Object* clone() const;

private:

};