#pragma once
#include <SFML/Graphics.hpp>

class Object
{
public:
	Object();
	~Object();
	void draw(sf::RenderWindow&) const;

private:
	sf::Sprite m_sprite;
};
