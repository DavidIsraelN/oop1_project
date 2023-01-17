#include "Objects/Cookie.h"
#include "Objects/Object.h"

Cookie::Cookie(const sf::Vector2f& position, float width, float height)
    : Erasable(*ResourceManage::Resource()->getCookieT(), position, width, height, 2) { }
