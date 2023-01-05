#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

const float PIXELS = 34;

class Object
{
public:
	//Object();
	//~Object();
	void draw(sf::RenderWindow&) const;

protected:
	sf::Sprite m_sprite;
};
