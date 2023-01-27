#include "Objects/Pacman.h"
#include "Level.h"

//-------------------------------------------------------------------
Pacman::Pacman(const sf::Vector2f& position, float width, float height)
    : MovingObj(ResourceManager::Resource().getObjTexture(ObjIndex::PACMAN_OPEN),
                position, width, height)
{
  m_move = std::make_unique<RegularMovement>();
}

//-------------------------------------------------------------------
void Pacman::setDirection(sf::Keyboard::Key key)
{
  switch (key) {
  case sf::Keyboard::Key::Space:   m_new_direction = sf::Vector2f ( 0, 0);   return;
  case sf::Keyboard::Key::Right:   m_new_direction = sf::Vector2f ( 1, 0);   return;
  case sf::Keyboard::Key::Left:    m_new_direction = sf::Vector2f (-1, 0);   return;
  case sf::Keyboard::Key::Up:      m_new_direction = sf::Vector2f ( 0,-1);   return;
  case sf::Keyboard::Key::Down:    m_new_direction = sf::Vector2f ( 0, 1);   return;
  }
}

//-------------------------------------------------------------------
void Pacman::move(const sf::Time& deltaTime, const Level& level, float win_height, float win_width)
{
  if(m_move->isLegal(m_new_direction * (m_sprite.getGlobalBounds().height / 3), level, *this, win_height, win_width))
  {
    //m_move->action(m_new_direction * speedPerSecond * deltaTime.asSeconds(), *this);
    moveObj(m_new_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);
    m_cur_direction = m_new_direction;
  }

  else if (m_move->isLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(),
                           level, *this, win_height, win_width))
    moveObj(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);

  rotateObj(m_cur_direction.y == 1 ? 90 : m_cur_direction.y == -1 ? 270 : m_cur_direction.x == -1 ? 180 : 0);
}

//-------------------------------------------------------------------
size_t Pacman::getLife() const
{
  return m_life;
}

//-------------------------------------------------------------------
size_t Pacman::getScore() const
{
  return m_score;
}

//-------------------------------------------------------------------
void Pacman::lifeReduction()
{
  if (m_life > 0)
    --m_life;
}

//-------------------------------------------------------------------
void Pacman::setScore(const size_t score)
{
  m_score = score;
}

//-------------------------------------------------------------------
void Pacman::setLife(const size_t life)
{
  m_life = life;
}

//-------------------------------------------------------------------
void Pacman::setAnimate(const sf::Time& delta_time)
{
  m_counter_seconds += delta_time.asSeconds();
  if (m_counter_seconds >= 0.2)
  {
    if (m_sprite.getTexture() == &ResourceManager::Resource().getObjTexture(ObjIndex::PACMAN_CLOSE))
      m_sprite.setTexture(ResourceManager::Resource().getObjTexture(ObjIndex::PACMAN_OPEN));
    else
      m_sprite.setTexture(ResourceManager::Resource().getObjTexture(ObjIndex::PACMAN_CLOSE));
    m_counter_seconds -= 0.2;
  }
}

//-------------------------------------------------------------------
void Pacman::stopSPacman()
{
  m_move = std::make_unique<RegularMovement>();
  m_sprite.setColor(sf::Color(255, 255, 255));
  m_spacman_clock = 0;
  is_super_pacman = false;
  Sound::Sounds().Stop(SoundIndex::S_PACMAN);
}

//-------------------------------------------------------------------
void Pacman::SPacmanClock(const sf::Time& delta_time)
{
  if (!is_super_pacman)
    return;
  m_spacman_clock += delta_time.asSeconds();
  if (m_spacman_clock >= 15)
    stopSPacman();

  if (m_spacman_clock < 12.5)
    return;
  m_colors_clock += delta_time.asSeconds();
  if (m_colors_clock >= 0.2)
  {
    if (m_sprite.getColor() == sf::Color(163, 23, 168))
      m_sprite.setColor(sf::Color(255, 255, 255));
    else
      m_sprite.setColor(sf::Color(163, 23, 168));
    m_colors_clock -= 0.2;
  }
}

bool Pacman::isSuperPacman() const
{
  return is_super_pacman;
}

//-------------------------------------------------------------------
void Pacman::collide(Object& object)
{
  object.collide(*this);
}

//-------------------------------------------------------------------
void Pacman::collide(Demon& demon)
{
  if (is_super_pacman)
    return;

  resetPosition();
  m_cur_direction = { 0, 0 };
  m_new_direction = { 0, 0 };

  Sound::Sounds().Play(SoundIndex::DEATH);
  --m_life;
}

//-------------------------------------------------------------------
void Pacman::collide(Cookie& cookie)
{
  m_score += 2;
}

//-------------------------------------------------------------------
void Pacman::collide(Key& key)
{
  m_score += 7;
}

//-------------------------------------------------------------------
void Pacman::collide(SuperPGift& super_p)
{
  is_super_pacman = true;
  m_move = std::make_unique<SPacmanMovement>();
  m_spacman_clock = 0;
  m_score += 5;
  m_sprite.setColor(sf::Color(163, 23, 168));
  Sound::Sounds().Play(SoundIndex::S_PACMAN);
}

//-------------------------------------------------------------------
void Pacman::collide(FreezeGift& freeze)
{
  m_score += 5;
}

//-------------------------------------------------------------------
void Pacman::collide(TimeGift& time)
{
  m_score += 5;
}

//-------------------------------------------------------------------
void Pacman::collide(LifeGift& life)
{
  ++m_life;
  m_score += 5;
}



//  auto win_height = obj_h * rows, win_width = obj_w * cols;

//if (directionLegal(m_new_direction * (obj_h / 2), win_height, win_width, level, obj_h, obj_w))
//{
//  moveObj(m_new_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, obj_h, obj_w);
//}

//else if(directionLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, level, obj_h, obj_w))
//  moveObj(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, obj_h, obj_w);

//
//  if (directionLegal(m_new_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, level, obj_h, obj_w))
//    m_cur_direction = m_new_direction;
//
//  else
//    directionLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, level, obj_h, obj_w);

//  if(m_cur_direction.x == -1 && m_scale == false)
//  {
//    m_sprite.scale(-1, 1);
//    m_scale = true;
//    return;
//  }
//  else if (m_cur_direction.x == 1 && m_scale == true)
//  {
//    m_sprite.scale(-1, 1);
//    m_scale = false;
//    return;
//  }
//
//  if (m_cur_direction.y == -1 || m_cur_direction.y == 1)
//  {
//    if(m_scale == true)
//    {
//      m_sprite.scale(-1, 1);
//      m_scale = false;
//    }
//    return;
//  }


//  if(m_cur_direction.x == 1)
//    m_sprite.scale(1, 1);


//else if (!directionLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, level))
//  m_cur_direction = { 0, 0 };


//if (directionLegal(getPosition() + m_new_direction * speedPerSecond * deltaTime.asSeconds(), level))
//  m_cur_direction = m_new_direction;

//else if (!directionLegal(getPosition() + m_cur_direction * speedPerSecond * deltaTime.asSeconds(), level))
//  m_cur_direction = { 0, 0 };

//auto direction = (m_cur_direction * speedPerSecond * deltaTime.asSeconds());

//if (getPosition().x + direction.x >= win_width)   direction.x = - win_width;
//else if (getPosition().x + direction.x <= 0.f)    direction.x = win_width;
//if (getPosition().y + direction.y >= win_height)  direction.y = -win_height;
//else if (getPosition().y + direction.y <= 0.f)    direction.y = win_height;

//moveObj(direction, win_height, win_width);
//rotateObj(m_cur_direction.y == 1 ? 90: m_cur_direction.y == -1 ? 270 : m_cur_direction.x == -1 ? 180 : 0);

//
//bool Pacman::directionLegal(const sf::Vector2f& direction, float win_height, float win_width, const Level& level, float obj_h, float obj_w)
//{
//  moveObj(direction, win_height, win_width, obj_h, obj_w);
//  if (level.collideWithWallOrDoor(*this))
//  {
//    moveObj(-direction, win_height, win_width, obj_h, obj_w);
//    return false;
//  }
//  moveObj(-direction, win_height, win_width, obj_h, obj_w);
//
//
//
//
//  //auto delta_x = getPosition().x;
//  //auto delta_y = getPosition().y;
//  //auto epsilon = float(10);
//
//  //while (delta_x >= obj_w)
//  //  delta_x -= obj_w;
//
//  //if (delta_x >= obj_w / 2 - epsilon && delta_x <= obj_w / 2 + epsilon) delta_x = obj_w / 2 - delta_x;
//
//  //while (delta_y >= obj_h)
//  //  delta_y -= obj_h;
//
//  //if (delta_y >= obj_h / 2 - epsilon && delta_y <= obj_h / 2 + epsilon) delta_y = obj_h / 2 - delta_y;
//
//  //moveObj({ delta_x, delta_y }, win_height, win_width, obj_h, obj_w);
//
//
//  //moveObj(-direction, win_height, win_width, obj_h, obj_w);
//  //moveObj(direction, win_height, win_width, obj_h, obj_w);
//
//  return true;
//  //if (type == DEMON|| type == DOOR)
//  //  return false;
//  //return true;
//}
