#include "Objects/Demon.h"
#include "Level.h"

//-------------------------------------------------------------------
Demon::Demon(const sf::Vector2f& position, float width, float height)
    : MovingObj(ResourceManager::Resource().getObjTexture(ObjIndex::DEMON), position, width, height)
{
  m_move = std::make_unique<RegularMovement>();
  m_new_direction = {0, -1};
  m_speed = NonRandomSpeed;
}

//-------------------------------------------------------------------
void Demon::move(const sf::Time& deltaTime, const Level& level, float win_height, float win_width)
{
  freezeClock(deltaTime);
  if (m_is_freeze) return;

  m_cur_direction = m_new_direction;
  auto pac = level.getPacmanPosition();
  setMode(deltaTime);
  m_new_direction = setDirection(pac, deltaTime, level, win_height, win_width);
  moveObj(m_cur_direction != m_new_direction ? m_new_direction * (m_sprite.getGlobalBounds().height / 10)
                                             : m_new_direction * m_speed * deltaTime.asSeconds(), win_height, win_width);
}

//-------------------------------------------------------------------
void Demon::setMode(const sf::Time& deltaTime)
{
  m_random_clock += deltaTime.asSeconds();
  if (m_random_clock >= 8)
  {
    m_speed = NonRandomSpeed;
    m_random_clock = 0;
  }
  else if (m_random_clock > 3)
    m_speed = RandomSpeed;
}

//-------------------------------------------------------------------
sf::Vector2f Demon::setDirection(const sf::Vector2f& pacman, const sf::Time& deltaTime,
                                 const Level& level, float win_h, float win_w)
{
  sf::Vector2f directions[4];
  directions[3] = -m_cur_direction;

  if (m_random_clock <= 3)
    setRandomDirection(directions);
  else {
    m_distance_x = pacman.x - m_sprite.getPosition().x;
    m_distance_y = pacman.y - m_sprite.getPosition().y;
    setNonRandomDirection(directions);
  }

  for (auto i = size_t(0); i < 4; ++i)
    if (m_move->isLegal(directions[i] == m_cur_direction ? directions[i] * m_speed * deltaTime.asSeconds() :
                        directions[i] * (m_sprite.getGlobalBounds().height / 3), level, *this, win_h, win_w))
      return directions[i];

  return { 0, 0 }; // shouldn't ever be used
}

//-------------------------------------------------------------------
void Demon::setNonRandomDirection(sf::Vector2f directions[])
{
  setFirstAndSecondDirection(directions);
  setThirdDirection(directions);
}

//-------------------------------------------------------------------
void Demon::setFirstAndSecondDirection(sf::Vector2f directions[])
{
  auto x_direction = m_distance_x > 0 ? sf::Vector2f(1, 0) : sf::Vector2f(-1, 0);
  auto y_direction = m_distance_y > 0 ? sf::Vector2f(0, 1) : sf::Vector2f(0, -1);

  if (std::abs(m_distance_y) > std::abs(m_distance_x))
  {
    directions[0] = y_direction == directions[3] ? x_direction : y_direction;
    directions[1] = x_direction == directions[0] || x_direction == directions[3] ? m_cur_direction : x_direction;
  }
  else
  {
    directions[0] = x_direction == directions[3] ? y_direction : x_direction;
    directions[1] = y_direction == directions[0] || y_direction == directions[3] ? m_cur_direction : y_direction;
  }
}

//-------------------------------------------------------------------
void Demon::setThirdDirection(sf::Vector2f directions[])
{
  if (m_cur_direction == directions[0] || m_cur_direction == directions[1])
    directions[2] = -(directions[0] + directions[1] + directions[3]);
  else
    directions[2] = m_cur_direction;
}

//-------------------------------------------------------------------
void Demon::setRandomDirection(sf::Vector2f directions[])
{
  for (auto i = size_t(0); i < 2;)
  {
    auto direction = sf::Vector2f( rand() % 3 - 1, rand() % 3 - 1);
    if (direction.x == direction.y || direction == directions[3] || (direction.x != 0 && direction.y != 0))
      continue;
    if (i == 1 && direction == directions[0])
      continue;
    directions[i++] = direction;
  }
  setThirdDirection(directions);
}

//-------------------------------------------------------------------
void Demon::collide(Pacman& pacman)
{
  Sound::Sounds().Play(SoundIndex::GHOST);
  resetPosition();
  pacman.collide(*this);
}

//-------------------------------------------------------------------
void Demon::freeze()
{
  m_is_freeze = true;
  m_freeze_clock = 0;
  m_sprite.setColor(SemiTransparent);
}

//-------------------------------------------------------------------
void Demon::freezeClock(const sf::Time&delta_time)
{
  if (!m_is_freeze) return;
  m_freeze_clock += delta_time.asSeconds();
  if (m_freeze_clock >= 10) stopFreeze();
  if (m_freeze_clock <= 8) return;

  blinkObject(delta_time, 0.2, SemiTransparent);
}

//-------------------------------------------------------------------
void Demon::stopFreeze()
{
  m_is_freeze = false;
  m_freeze_clock = 0;
  m_sprite.setColor(Opacity);
}