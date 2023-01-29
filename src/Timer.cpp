#include "Timer.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Colors.h"

//-------------------------------------------------------------------
void Timer::updateTimer(const sf::Time& delta_time)
{
  m_elapsed += delta_time.asSeconds();
  m_time_left = m_time_start - m_elapsed;

  auto minutes = m_time_left / 60 % 60;
  auto seconds = m_time_left % 60;

  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << minutes << ":"
     << std::setfill('0') << std::setw(2) << seconds;

  m_timer = ss.str();
}

//-------------------------------------------------------------------
void Timer::setStart(size_t board_num)
{
  switch (board_num)
  {
  case 1:  m_time_start = 3 * 60 + 1;  break;
  case 2:  m_time_start = 4 * 60 + 1;  break;
  case 3:  m_time_start = 5 * 60 + 1;  break;
  }
  m_elapsed = 0;
}

//-------------------------------------------------------------------
void Timer::addTime(size_t add)
{
  m_time_start += add;
}

//-------------------------------------------------------------------
std::string Timer::getTimer() const
{
  return m_timer;
}

//-------------------------------------------------------------------
sf::Color Timer::getColor() const
{
  return m_time_left > 30 ? DeepRed : sf::Color::Red;
}

//-------------------------------------------------------------------
bool Timer::isOver() const
{
  return m_time_left == 0 ? true : false;
}