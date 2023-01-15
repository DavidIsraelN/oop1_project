#pragma once
#include "MovingObj.h"

const auto speedPerSecond = 130.f;
class Level;

class Pacman : public MovingObj
{
public:
	Pacman(const sf::Texture&, const sf::Vector2f&, float, float);
	void setDirection(sf::Keyboard::Key) override;
	//void move(sf::Time) override;
	void move(sf::Time, float, float, float, float, const Level&);
	//	void collusion() override;

private:
	bool directionLegal(const sf::Vector2f&, float, float, const Level&, float, float);
	sf::Vector2f m_cur_direction = { 0, 0 };
	sf::Vector2f m_new_direction = { 0, 0 };
	size_t m_hearts = 3;
	size_t score = 0;
};