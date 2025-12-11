#include "player.hpp"

Player::Player()
    : Shooter()
{
}

std::unique_ptr<Bullet> Player::shoot()
{
  return std::make_unique<Bullet>(getPosX() + getWidth() / 2,
      getPosY() - 1, -1);
}