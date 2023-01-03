#pragma once
#include <SFML/Graphics.hpp>

class Batton
{
public:
	Batton();
	~Batton();
	void draw(sf::RenderWindow&) const;
	virtual void action() = 0;

private:
	fs::Text text;
}
