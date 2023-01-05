#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button();
	~Button();
	void draw(sf::RenderWindow&) const;
	virtual void action() = 0;

private:
	sf::Text text;
};