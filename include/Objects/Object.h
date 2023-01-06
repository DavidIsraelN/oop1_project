#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

const float PIXELS = 34;

class Object
{
public:
	Object(const sf::Texture&, const sf::Vector2f&, float, float, float);
	//~Object();
	void draw(sf::RenderWindow&) const;

private:
	sf::Sprite m_sprite;
};
