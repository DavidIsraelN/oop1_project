#pragma once
#include "Button.h"
#include "Controller.h"
#include "../Colors.h"

class Mute : public Button
{
public:
	Mute(sf::Font& font, const sf::Vector2f& position, size_t size)
		: Button("Mute", font, position, size, sf::Color::White) { }

	bool action(sf::RenderWindow& window, Controller& c) override
	{ 
		if (m_muted) { m_muted = false; c.mute(m_muted); }
		else         { m_muted = true;  c.mute(m_muted); }
		return false;
	}

private:
	bool m_muted = false;
};