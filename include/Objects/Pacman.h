#pragma once
#include "MovingObj.h"

const auto speedPerSecond = 100.f;

class Pacman : public MovingObj
{
public:
	Pacman(const sf::Texture&, const sf::Vector2f&, float, float);
	void setDirection(sf::Keyboard::Key) override;
	void move(sf::Time) override;
	void move(sf::Time, float, float);
	//	void collusion() override;

private:
	size_t m_hearts = 3;
	sf::Vector2f m_direction = { 0, 0 };
};