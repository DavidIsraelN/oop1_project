#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Timer
{
public:
  void updateTimer(int);
  void setStart(int);
  void addTime(int);
  std::string getTimer() const;

private:
  int m_time_start, m_time_left;
  std::string m_timer;
};