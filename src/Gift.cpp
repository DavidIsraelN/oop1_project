#include "Objects/Gift.h"

Gift::Gift(const sf::Vector2f& position, float width, float height)
    : Erasable(*ResourceManage::Resource()->getGiftT(), position, width, height, 1.5) { }
