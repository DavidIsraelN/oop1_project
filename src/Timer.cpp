#include "Timer.h"
#include <iostream>
#include <sstream>
#include <iomanip>

//-------------------------------------------------------------------
void Timer::updateTimer(size_t elapsed)
{
  m_time_left = m_time_start - elapsed;

  auto minutes = static_cast<size_t>(m_time_left) / 60 % 60;
  auto seconds = static_cast<size_t>(m_time_left) % 60;

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
  case 1:  m_time_start = static_cast<size_t>(3) * 60;  break;
  case 2:  m_time_start = static_cast<size_t>(4) * 60;  break;
  case 3:  m_time_start = static_cast<size_t>(5) * 60;  break;
  }
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
void Timer::pause()
{

}
