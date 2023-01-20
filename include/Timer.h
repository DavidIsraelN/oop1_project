#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Timer
{
public:
  void updateTimer(size_t);
  void setStart(size_t);
  void pause();
  void addTime(size_t);
  std::string getTimer() const;

private:
  size_t m_time_start, m_time_left;
  std::string m_timer;
};