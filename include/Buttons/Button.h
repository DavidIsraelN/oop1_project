#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManage.h"

class Controller;

class Button
{
public:
  Button(const std::string&, const sf::Vector2f&, size_t, sf::Color);
  virtual ~Button() { }
  void draw(sf::RenderWindow&) const;
  bool clickMe(const sf::Vector2f&) const;
  virtual bool action(sf::RenderWindow&, Controller&) = 0;

private:
  sf::Text m_text;
  //sf::RectangleShape m_rectangle;
  //sf::Sprite m_sprite;
};