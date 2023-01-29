#pragma once
#include <SFML/Graphics.hpp>
//#include "ResourceManager.h"
//#include <iostream>

class Pacman;
class Wall;
class Cookie;
class Key;
class Door;
class SuperPGift;
class FreezeGift;
class TimeGift;
class LifeGift;
class Demon;

class Object
{
public:
  Object(const sf::Texture&, const sf::Vector2f&, float, float, float);
  virtual ~Object() { }
  void draw(sf::RenderWindow&) const;
  bool collidesWith(Object&) const;
  void moveObj(const sf::Vector2f&, float, float);

  virtual void collide(Object&) = 0;
  virtual void collide(Pacman&) = 0;
  virtual void collide(Cookie&) = 0;
  virtual void collide(SuperPGift&) = 0;
  virtual void collide(FreezeGift&) = 0;
  virtual void collide(TimeGift&) = 0;
  virtual void collide(LifeGift&) = 0;
  virtual void collide(Key&) = 0;
  virtual void collide(Wall&) = 0;
  virtual void collide(Door&) = 0;
  virtual void collide(Demon&) = 0;

  //virtual void collide( & other_obj) = 0;
  //virtual void collide( & other_obj) = 0;

protected:
//  void moveObj(const sf::Vector2f&, float, float, float, float);
  void rotateObj(float);
  sf::Sprite m_sprite;
};
