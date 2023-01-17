#include "Objects/Key.h"

Key::Key(const sf::Vector2f& position, float width, float height)
    : Erasable(*ResourceManage::Resource()->getKeyT(), position, width, height, 1.5) { }
