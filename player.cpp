#include "player.hpp"

Player::Player()
    : Shooter()
{
}

Player::Player(int p_x, int p_y)
    : Shooter(p_x, p_y)
{
}

std::unique_ptr<Bullet> Player::shoot()
{
  return std::make_unique<Bullet>(getPosX() + getWidth() / 2,
      getPosY() - 1, -1);
}