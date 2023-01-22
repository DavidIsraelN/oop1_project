#pragma once
#include <SFML/Audio.hpp>
#include "ResourceManager.h"

class Sound
{
public:
  static Sound& Sounds()
  {
    static auto m_sound = Sound();
    return m_sound;
  }

  Sound(const Sound&) = delete;
  void operator=(const Sound&) = delete;

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

  bool isMute() const { return m_muted;}

private:
  Sound()
  {
    for (auto i = size_t(0); i < SOUND; ++i)
      m_sounds[i].setBuffer(
          ResourceManager::Resource().getSound(SoundIndex(i)));
  }

  sf::Sound m_sounds [SOUND];
  bool m_muted = false;
};