#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

const float PIXELS = 34;

class Object
{
public:
	Object(const sf::Texture&, const sf::Vector2f&, float, float, float);
	virtual ~Object() { }
	void draw(sf::RenderWindow&) const;
	sf::Vector2f getPosition() const;
	void moveObj(const sf::Vector2f&);
	void rotateObj(float);

private:
	sf::Sprite m_sprite;
};
