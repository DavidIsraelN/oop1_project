#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

//-------------------------------------------------------------------
const size_t OBJECTS = 11;
const size_t FILES = 4;
const size_t SOUND = 6;

//-------------------------------------------------------------------
enum class ObjIndex
{
  COOKIE, DOOR, KEY, GIFT, FREEZE, TIMER,
  LIFE, WALL, PACMAN_OPEN, PACMAN_CLOSE, DEMON
};

enum class TxtIndex
{
  LEVEL1, LEVEL2, LEVEL3, HELP
};

enum class SoundIndex
{
  START, LEVEL_RUN, COOKIE, GIFTS, S_PACMAN, DEATH
};

//-------------------------------------------------------------------
class ResourceManager
{
public:
  static ResourceManager& Resource()
  {
    static auto m_resource = ResourceManager();
    return m_resource;
  }

  ResourceManager(const ResourceManager&) = delete;
  void operator=(const ResourceManager&) = delete;

  sf::Image& getIcon()                        { return m_icon; }
  sf::Font& getFont()                         { return m_font; }
  sf::Texture& getObjTexture(ObjIndex type)   { return m_objects_texture[size_t(type)]; }
  std::ifstream& getTxtFile(TxtIndex type)    { return m_files[size_t(type)]; }
  sf::SoundBuffer& getSound(SoundIndex type)  { return m_sounds[size_t(type)]; }

private:
  ResourceManager()
  {
//    m_font.loadFromFile("Arial.ttf");
    m_font.loadFromFile("crackman.front-regular.otf");
    m_icon.loadFromFile("pacman.png");

    for (auto i = size_t(0); i < OBJECTS; ++i)
      m_objects_texture[i].loadFromFile(m_textures_name[i]);

    for (auto i = size_t(0); i < FILES; ++i)
      m_files[i] = std::ifstream(m_files_name[i]);

    for (auto i = size_t(0); i < SOUND; ++i)
      m_sounds[i].loadFromFile(m_sounds_name[i]);
  }

  std::string m_textures_name[OBJECTS] =
      { "cookie.png","door.png","key.png","gift.png","freeze.png", "timer.png",
        "life.png","wall.jpg","pacman_open.png","pacman_close.png","demon.png" };
  sf::Texture m_objects_texture[OBJECTS];

  std::string m_sounds_name[SOUND] =
      { "intermission.wav", "game_start.wav", "credit.wav", "eat_fruit.wav" ,
        "retreating.wav", "death_1.wav" };
  sf::SoundBuffer m_sounds[SOUND];

  std::string m_files_name[FILES] = { "Level_1.txt", "Level_2.txt", "Level_3.txt", "Help.txt" };
  std::ifstream m_files[FILES];

  sf::Font m_font;
  sf::Image m_icon;
};
