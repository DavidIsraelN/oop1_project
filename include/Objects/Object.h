#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManage.h"
//#include <queue>

#include <iostream>

//const float PIXELS = 34;

class Pacman;
class Wall;
class Cookie;
class Gift;
class Key;

class Object
{
public:
  Object(const sf::Texture&, const sf::Vector2f&, float, float, float);
  virtual ~Object() { }
  void draw(sf::RenderWindow&) const;
  sf::Vector2f getPosition() const;
  sf::FloatRect getGlobalBounds() const;
  void moveObj(const sf::Vector2f&, float, float, float, float);
  void rotateObj(float);
  bool collidesWith(Object&) const;

  virtual void collide(Object&) = 0;
  virtual void collide(Pacman&) = 0;
  virtual void collide(Cookie&) = 0;
  virtual void collide(Gift&) = 0;
  virtual void collide(Key&) = 0;

  //virtual void collide(& other_obj) = 0;
  //virtual void collide(& other_obj) = 0;

protected:
  sf::Sprite m_sprite;
//  std::queue<sf::Sound> m_sound_obj;
};
