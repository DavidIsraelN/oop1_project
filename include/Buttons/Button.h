#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "LevelManager.h"
#include "../Colors.h"

// Abstract class for all button types

class LevelManager;

class Button
{
public:
  Button(const std::string&, const sf::Vector2f&, size_t, sf::Color);
  virtual ~Button() { }
  void draw(sf::RenderWindow&) const;
  bool clickMe(const sf::Vector2f&) const;
  virtual bool action(sf::RenderWindow&, LevelManager&) = 0;

protected:
  sf::Text m_text;
};