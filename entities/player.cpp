#include "player.hpp"

Player::Player()
    : Shooter()
{
  const std::vector<std::vector<char>> appearance = {
    { '/', '|', '|', '\\' },
    { '|', '0', '0', '|' },
    { ' ', '|', '|', ' ' }
  };
  setAppearance(appearance);
  setWidth(appearance[0].size());
  setHeight(appearance.size());
  setPosX(WIDTH / 2);
  setPosY(HEIGHT - BORDER_SIZE - appearance.size());
}

std::unique_ptr<Bullet> Player::shoot()
{
  if (canShoot())
  {
    setShootTime(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch())
            .count());
    return std::make_unique<Bullet>(getPosX() + getWidth() / 2,
        getPosY() - 1, -1);
  }
  return nullptr;
}