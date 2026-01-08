#include "bullet.hpp"

Bullet::Bullet(
    int                                   p_x,
    int                                   p_y,
    BulletDirection                       direction,
    unsigned short                        color_pair,
    const std::vector<std::vector<char>>& appearance)
    : Entity()
    , direction_(direction)
{
  setAppearance(appearance);
  setHeight(appearance.size());
  setWidth(appearance[0].size());
  setPosX(p_x);
  setPosY(p_y);
  setColor(color_pair);
}

void Bullet::update(short delta_x, short delta_y)
{
  setPosY(static_cast<int>(getPosY() + static_cast<int>(direction_)));
}