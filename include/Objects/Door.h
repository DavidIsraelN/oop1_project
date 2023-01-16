#pragma once
#include "Erasable.h"

//class Erasable;

class Door : public Erasable
{
public:
	Door(const sf::Texture&, const sf::Vector2f&, float, float);
//	~Door();
        void collide(Pacman& pacman) override { }
        void collide(Object& obj) override {
          delObj();
          obj.collide(*this); }
private:

};