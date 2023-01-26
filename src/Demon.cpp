#include "Objects/Demon.h"
#include "Level.h"

Demon::Demon(const sf::Vector2f& position, float width, float height)
    : MovingObj(ResourceManager::Resource().getObjTexture(ObjIndex::DEMON), position, width, height)
{
  m_move = std::make_unique<PacmanMovement>();
}

void Demon::move(const sf::Time& deltaTime, const Level& level, float win_height, float win_width)
{
  auto pac = level.getPacmanPosition();
  m_cur_direction = setDirection(pac, deltaTime, level, win_height, win_width);
  moveObj(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);

  //if(m_move->isLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), level, *this, win_height, win_width))
  //  moveObj(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);

  //else if(m_move->isLegal(m_new_direction * (m_sprite.getGlobalBounds().height / 3), level, *this, win_height, win_width))
  //{
  //  moveObj(m_new_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);
  //  m_cur_direction = m_new_direction;
  //}


}

sf::Vector2f Demon::setDirection(const sf::Vector2f& pacman, const sf::Time& deltaTime,
                                 const Level& level, float win_h, float win_w)
{
  m_distance_x = pacman.x - m_sprite.getPosition().x;
  m_distance_y = pacman.y - m_sprite.getPosition().y;

  sf::Vector2f directions[4];
  directions[3] = m_cur_direction;

  setNonRandomDirection(directions);

  for (int i = 0; i < 3; ++i)
    if (m_move->isLegal(directions[i] * speedPerSecond * deltaTime.asSeconds(), level, *this, win_h, win_w))
      return directions[i];

  std::cout << "ERROR" << std::endl;
  return { -1, 0 };
  //
  //  m_demons[j] = m_old_demons[j];
}

void Demon::setNonRandomDirection(sf::Vector2f directions[])
{
  setFirstAndSecondDirection(directions);
  setThirdDirection(directions);
}

void Demon::setFirstAndSecondDirection(sf::Vector2f directions[])
{
  auto x_direction = m_distance_x > 0 ? sf::Vector2f(1, 0) : sf::Vector2f(-1, 0);
  auto y_direction = m_distance_y > 0 ? sf::Vector2f(0, 1) : sf::Vector2f(0, -1);

  if (std::abs(m_distance_y) > std::abs(m_distance_x))
  {
    directions[0] = y_direction;
    directions[1] = x_direction;
  }
  else
  {
    directions[0] = x_direction;
    directions[1] = y_direction;
  }
}

void Demon::setThirdDirection(sf::Vector2f directions[])
{
  if (directions[3] == sf::Vector2f{ 0, 0 })
  {
    directions[2] = { 1, 0 };
  }

  directions[2] = directions[0] + directions[1] + directions[3];
  if (directions[2].x != 0)
    directions[2].x *= (-1);

  if (directions[2].y != 0)
    directions[2].y *= (-1);

  //  if (directions[2].x != 0 && directions[2].y != 0)
  //    directions[2] = {1, 0};

}





void Demon::move(const sf::Time& deltaTime, const Level& level, float win_height, float win_width, int l)
{
  if (m_distance_x >= level.getObjDimensions().x || m_distance_y >= level.getObjDimensions().y)
  {
    sf::Vector2f demon_position = {(m_sprite.getPosition().x - level.getObjDimensions().x / 2) / level.getObjDimensions().x,
                                   (m_sprite.getPosition().y - level.getObjDimensions().y / 2) / level.getObjDimensions().y};

    sf::Vector2f pacman_position = {(level.getPacmanPosition().x - level.getObjDimensions().x / 2) / level.getObjDimensions().x,
                                    (level.getPacmanPosition().y - level.getObjDimensions().y / 2) / level.getObjDimensions().y};

    std::cout << "Pacman position: " << pacman_position.x << ' ' << pacman_position.y << std::endl;
    std::cout << "Demon position: " << demon_position.x << ' ' << demon_position.y << std::endl;

//    Location old_loc = m_demons[j];
    auto new_direction = setDirection(level.getMat(), demon_position, pacman_position);

    std::cout << "new direction: " << new_direction.x << ' ' << new_direction.y << std::endl;
    auto old_position = m_sprite.getPosition();
    if(m_move->isLegal(new_direction * (m_sprite.getGlobalBounds().height / 3), level, *this, win_height, win_width))
    {
      //m_move->action(m_new_direction * speedPerSecond * deltaTime.asSeconds(), *this);
      moveObj(new_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);
      m_cur_direction = new_direction;
    }
    else if (m_move->isLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(),
                             level, *this, win_height, win_width))
      moveObj(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);

//  moveObj(new_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);
    auto new_position = m_sprite.getPosition();
    m_distance_x = abs(old_position.x - new_position.x);
    m_distance_y = abs(old_position.y - new_position.y);
//    m_cur_direction = new_direction;
  }
  else
  {
    auto old_position = m_sprite.getPosition();
    if (m_move->isLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(),
                             level, *this, win_height, win_width))
        moveObj(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);
    auto new_position = m_sprite.getPosition();
    m_distance_x += abs(old_position.x - new_position.x);
    m_distance_y += abs(old_position.y - new_position.y);
  }

//  if(m_move->isLegal(new_direction * (m_sprite.getGlobalBounds().height / 3), level, *this, win_height, win_width))
//  {
//    //m_move->action(m_new_direction * speedPerSecond * deltaTime.asSeconds(), *this);
//    moveObj(new_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);
//    m_cur_direction = new_direction;
//  }
//
//  else if (m_move->isLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(),
//                           level, *this, win_height, win_width))
//  moveObj(new_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);
//
//  if(m_move->isLegal(new_direction * (m_sprite.getGlobalBounds().height / 3), level, *this, win_height, win_width))
//  {
//    //m_move->action(m_new_direction * speedPerSecond * deltaTime.asSeconds(), *this);
//    moveObj(new_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);
//    m_cur_direction = new_direction;
//  }
//
//  else if (m_move->isLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(),
//                           level, *this, win_height, win_width))
//    moveObj(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width);

//  rotateObj(m_cur_direction.y == 1 ? 90 : m_cur_direction.y == -1 ? 270 : m_cur_direction.x == -1 ? 180 : 0);

//    if (c.getPacmanLocation() == m_demons[j] && !c.superPacmanActive()) {
//      m_steps = 0;
//      c.resetLevel();
//      return;
//    }
//    c.updateLevel(m_demons[j], '&');
//    m_old_demons[j] = old_loc;
//  }
//  ++m_steps;
}
////
//enum DemonDirection
//{
//  Null, Up, Right, Down, Left
//};


sf::Vector2f Demon::setDirection(const std::vector<std::vector<size_t>>& mat, const sf::Vector2f& demon, const sf::Vector2f& pacman)
{
  sf::Vector2f directions[4];
  directions[3] = m_cur_direction;
//  DemonDirection directions[4] = { };
//  setForthDirection(directions[3]);

//  if (m_steps % 30 < 10)
//    setRandomDirection(directions);
//  else
  setNonrandomDirection(directions, mat, demon, pacman);
//
  for (int i = 0; i < 3; ++i)
    if (setNext(directions[i], mat, demon))
      return directions[i];

  std::cout << "ERROR" << std::endl;
  return {-1, 0};
//
//  m_demons[j] = m_old_demons[j];
}



void Demon::setNonrandomDirection(sf::Vector2f directions[], const std::vector<std::vector<size_t>>& mat, const sf::Vector2f& demon, const sf::Vector2f& pacman)
{
  setFirstAndSecondLocation(directions, mat, demon, pacman);
  setThirdDirection(directions, mat, demon, pacman);
}
////
////void Demon::setRandomDirection(DemonDirection* d) const
////{
////  srand(time(0));
////  for (int i = 0; i < 4; ++i)
////    while (true)
////    {
////      auto choice = (rand() % 4) + 1;
////
////      int j;
////      for (j = 0; j < i; ++j)
////        if (d[j] == DemonDirection(choice))
////          break;
////
////      if(j == i) {
////        d[i] = DemonDirection(choice);
////        break;
////      }
////    }
////}
////
////
void Demon::setFirstAndSecondLocation(sf::Vector2f directions[], const std::vector<std::vector<size_t>>& mat, const sf::Vector2f& demon, const sf::Vector2f& pacman)
{
  auto row_distance = pacman.y - demon.y;
  auto col_distance = pacman.x - demon.x;

  if (abs(row_distance) > abs(col_distance))
  {
    directions[0] = pacman.y > demon.y ? sf::Vector2f (0, 1) : sf::Vector2f (0, -1);
    directions[1] = pacman.x > demon.x ? sf::Vector2f (1, 0) : sf::Vector2f (-1, 0);
  }
  else
  {
    directions[0] = pacman.x > demon.x ? sf::Vector2f (1, 0) : sf::Vector2f (-1, 0);
    directions[1] = pacman.y > demon.y ? sf::Vector2f (0, 1) : sf::Vector2f (0, -1);
  }
//
//  for (auto i = size_t(0); i < 2; ++i)
//  {
//    if (directions[i] == directions[3])
//    {
//      if (directions[i] == sf::Vector2f {0, -1}) {
//        directions[i] = sf::Vector2f(0, 1);
//        break;
//      }
//      if (directions[i] == sf::Vector2f {0, 1}) {
//        directions[i] = sf::Vector2f(0, -1);
//        break;
//      }
//
//      if (directions[i] == sf::Vector2f {1, 0}) {
//        directions[i] = sf::Vector2f(-1, 0);
//        break;
//      }
//
//      if (directions[i] == sf::Vector2f {-1, 0}) {
//        directions[i] = sf::Vector2f(1, 0);
//        break;
//      }
//    }
//  }
}

void Demon::setThirdDirection(sf::Vector2f directions[], const std::vector<std::vector<size_t>>& mat, const sf::Vector2f& demon, const sf::Vector2f& pacman)
{
  if (directions[3] == sf::Vector2f {0, 0})
  {
    directions[2] = {1, 0};
  }
  directions[2] = directions[0] + directions[1] + directions[3];
  if (directions[2].x != 0)
    directions[2].x *= (-1);

  if (directions[2].y != 0)
    directions[2].y *= (-1);

//  if (directions[2].x != 0 && directions[2].y != 0)
//    directions[2] = {1, 0};
}

bool Demon::setNext(sf::Vector2f& direction, const std::vector<std::vector<size_t>>& mat, const sf::Vector2f& demon)
{
  sf::Vector2f new_location = demon;
  if (direction == sf::Vector2f {0, -1})
  {
    new_location.y = int(demon.y + mat.size() - 1) % (mat.size());
    if (isLegal(new_location, mat))
      return true;
    return false;
  }

  if (direction == sf::Vector2f {0, 1})
  {
    new_location.y = int(demon.y + 1) % (mat.size());
    if (isLegal(new_location, mat))
      return true;
    return false;
  }

  if (direction == sf::Vector2f {1, 0})
  {
    new_location.x = int(demon.x + 1) % (mat[0].size());
    if (isLegal(new_location, mat))
      return true;
    return false;
  }

  if (direction == sf::Vector2f {-1, 0})
  {
    new_location.x = int(demon.x + mat[0].size() - 1) % (mat[0].size());
    if (isLegal(new_location, mat))
      return true;
    return false;
  }

  return false;
}

bool Demon::isLegal(sf::Vector2f& new_location, const std::vector<std::vector<size_t>>& mat) const
{
  int i = new_location.y, j = new_location.x;
  return mat[i][j] == 0;
//  return c.getTypeInLoc(new_loc) != '#' &&
//         c.getTypeInLoc(new_loc) != 'D' &&
//         !(new_location == m_old_demons[i]);
}
