#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include <iostream>

//const float PIXELS = 34;

class Pacman;
class Wall;
class Cookie;
class Gift;
class Key;
class Door;

class Object
{
public:
  Object(const sf::Texture&, const sf::Vector2f&, float, float, float);
  virtual ~Object() { }
  void draw(sf::RenderWindow&) const;
  bool collidesWith(Object&) const;

  virtual void collide(Object&) = 0;
  virtual void collide(Pacman&) = 0;
  virtual void collide(Cookie&) = 0;
  virtual void collide(Gift&) = 0;
  virtual void collide(Key&) = 0;
  virtual void collide(Wall&) = 0;
  virtual void collide(Door&) = 0;

  //virtual void collide( & other_obj) = 0;
  //virtual void collide( & other_obj) = 0;

protected:
//  void moveObj(const sf::Vector2f&, float, float, float, float);
  void moveObj(const sf::Vector2f&, float, float);
  void rotateObj(float);
  sf::Sprite m_sprite;
//  std::queue<sf::Sound> m_sound_obj;
};
