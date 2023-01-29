#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/*
 * Class that is responsible for the time of the game
 */

class Timer
{
public:
  void updateTimer(const sf::Time&);
  void setStart(size_t);
  void addTime(size_t);
  std::string getTimer() const;
  sf::Color getColor() const;
  bool isOver() const;

private:
  size_t m_time_start, m_time_left;
  std::string m_timer;
  float m_elapsed = 0;
};
