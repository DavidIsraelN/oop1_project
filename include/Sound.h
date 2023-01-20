#pragma once
#include <SFML/Audio.hpp>
#include "ResourceManager.h"

class Sound
{
public:
  static Sound* Sounds()
  {
    static Sound m_sound;
    return &m_sound;
  }
  
  void Play(SoundIndex type)
  {
    if (m_muted) return;
    m_sounds[size_t(type)].play();
  }

  void Mute() 
  { 
    m_muted = !m_muted;
    if(!m_muted) return;
    for (auto i = size_t(0); i < SOUND; ++i)
      m_sounds[i].stop();
  }

private:
  Sound()
  {
    for (auto i = size_t(0); i < SOUND; ++i)
      m_sounds[i].setBuffer(ResourceManager::Resource()->getsound(SoundIndex(i)));
  }

  static Sound* m_sound;
  sf::Sound m_sounds [SOUND];
  bool m_muted = false;
};