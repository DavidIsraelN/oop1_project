#pragma once
#include <SFML/Graphics.hpp>
//#include <string>

class Timer
{
public:
  void updateTimer(const sf::Time&);
  void setStart(size_t);
//  void pause();
  void addTime(size_t);
  std::string getTimer() const;
  sf::Color getColor() const;
  bool isOver() const;

private:
  size_t m_time_start, m_time_left;
  std::string m_timer;
  float m_elapsed = 0;
//  bool m_pause = false;
};