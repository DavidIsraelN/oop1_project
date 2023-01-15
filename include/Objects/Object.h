#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

//const float PIXELS = 34;

class Pacman;
class Wall;

class Object
{
public:
	Object(const sf::Texture&, const sf::Vector2f&, float, float, float);
	virtual ~Object() { }
	void draw(sf::RenderWindow&) const;
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	void moveObj(const sf::Vector2f&, float, float);
	void rotateObj(float);
	bool collidesWith(const Object&) const;

	//virtual void collide(const Pacman&) = 0;
	//virtual void collide(const Wall&) = 0;
	//virtual void collide(& other_obj) = 0;
	//virtual void collide(& other_obj) = 0;


private:
	sf::Sprite m_sprite;
};
