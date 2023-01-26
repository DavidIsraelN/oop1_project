#pragma once
#include "MovingObj.h"

class Demon : public MovingObj
{
public:
  Demon(const sf::Vector2f&, float, float);

  void move(const sf::Time&, const Level&, float, float) override;
  sf::Vector2f setDirection(const sf::Vector2f&, const sf::Time&, const Level&, float, float);
  void setNonRandomDirection(sf::Vector2f[]);
  void setFirstAndSecondDirection(sf::Vector2f[]);
  void setThirdDirection(sf::Vector2f[]);



  void move(const sf::Time&, const Level&, float, float, int);

  sf::Vector2f setDirection(const std::vector<std::vector<size_t>>&, const sf::Vector2f&, const sf::Vector2f&);
  //
  void setNonrandomDirection(sf::Vector2f[], const std::vector<std::vector<size_t>>&,
                             const sf::Vector2f&, const sf::Vector2f&);

  void setFirstAndSecondLocation(sf::Vector2f[], const std::vector<std::vector<size_t>>&,
                                        const sf::Vector2f&, const sf::Vector2f&);

  void setThirdDirection(sf::Vector2f[], const std::vector<std::vector<size_t>>&,
                                const sf::Vector2f&, const sf::Vector2f&);

  bool setNext(sf::Vector2f&, const std::vector<std::vector<size_t>>&, const sf::Vector2f&);

  bool isLegal(sf::Vector2f&, const std::vector<std::vector<size_t>>&) const;




  ////
  ////void Demon::setRandomDirection(DemonDirection* d) const
  ////{
  ////  srand(time(0));
  ////  for (int i = 0; i < 4; ++i)
  ////    while (true)
  ////    {
  ////      auto choice = (rand() % 4) + 1;
  ////
  ////      int j;
  ////      for (j = 0; j < i; ++j)
  ////        if (d[j] == DemonDirection(choice))
  ////          break;
  ////
  ////      if(j == i) {
  ////        d[i] = DemonDirection(choice);
  ////        break;
  ////      }
  ////    }
  ////}
  ////
  ////


  void collide(Object&)     override { }
  void collide(Cookie&)     override { }
  void collide(SuperPGift&) override { }
  void collide(FreezeGift&) override { }
  void collide(TimeGift&)   override { }
  void collide(LifeGift&)   override { }
  void collide(Key&)        override { }
  void collide(Wall&)       override { }
  void collide(Door&)       override { }

private:
  float m_distance_x = 1000, m_distance_y = 1000;
};
