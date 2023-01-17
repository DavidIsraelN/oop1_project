#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Timer
{
public:
  Timer();
  //Timer(size_t);
  void setTimer(int);
  void setStart(int);
  void addTime(int);
  std::string getTimer() const;
  void draw(sf::RenderWindow&) const;

private:
  int m_time_start, m_time_left;
  sf::Text m_text;
};