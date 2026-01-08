#include "player.hpp"

Player::Player()
    : Entity()
{
  const std::vector<std::vector<char>> appearance = {
    { '/', '|', '|', '\\' },
    { '|', '0', '0', '|' },
    { ' ', '|', '|', ' ' }
  };
  setAppearance(appearance);
  setWidth(appearance[0].size());
  setHeight(appearance.size());
  setPosX(PLAYFIELD_WIDTH / 2);
  setPosY(PLAYFIELD_HEIGHT - BORDER_SIZE - appearance.size());
  setHealth(3);
}
std::unique_ptr<Bullet> Player::shoot()
{
  if (canShoot())
  {
    resetReloadFrameDelay();
    return std::make_unique<Bullet>(
        getPosX() + getWidth() / 2,
        getPosY() - 1,
        Bullet::BulletDirection::UP,
        getBulletColor(),
        getBulletAppearance());
  }
  return nullptr;
}