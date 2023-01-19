#include "Timer.h"
#include <iostream>
#include <sstream>
#include <iomanip>

void Timer::updateTimer(int elapsed)
{
  m_time_left = m_time_start - elapsed;

  int minutes = static_cast<int>(m_time_left) / 60 % 60;
  int seconds = static_cast<int>(m_time_left) % 60;

  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << minutes << ":"
     << std::setfill('0') << std::setw(2) << seconds;

  m_timer = ss.str();
}

void Timer::setStart(int board_num)
{
  switch (board_num)
  {
  case 1:
    m_time_start = 3 * 60;
    break;
  case 2:
    m_time_start = 4 * 60;
    break;
  case 3:
    m_time_start = 5 * 60;
    break;
  }
}

void Timer::addTime(int add)
{
  m_time_start += add;
}

std::string Timer::getTimer() const
{
  return m_timer;
}