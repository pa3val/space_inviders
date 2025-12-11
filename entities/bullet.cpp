#include "bullet.hpp"

#include "entity.hpp"

Bullet::Bullet(int p_x, int p_y, short direction)
    : Entity()
    , direction(direction)
{
  std::vector<std::vector<char>> appearance = {
    { '|' },
  };
  setAppearance(appearance);
  setHeight(appearance.size());
  setWidth(appearance[0].size());
  setPosX(p_x);
  setPosY(p_y);
}

void Bullet::update()
{
  setPosY(static_cast<int>(getPosY() + direction));
}