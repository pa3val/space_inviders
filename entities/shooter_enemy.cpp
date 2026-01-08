#include "shooter_enemy.hpp"

ShooterEnemy::ShooterEnemy()
    : Enemy()
{
}

std::unique_ptr<Bullet> ShooterEnemy::shoot()
{
  if (canShoot())
  {
    resetReloadFrameDelay();
    return std::make_unique<Bullet>(
        getPosX() + getWidth() / 2,
        getPosY() + getHeight(),
        Bullet::BulletDirection::DOWN,
        getBulletColor(),
        getBulletAppearance());
  }
  return nullptr;
}