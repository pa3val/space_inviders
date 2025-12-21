#include "enemy.hpp"

Enemy::Enemy()
    : Entity()
{
  const std::vector<std::vector<char>> appearance = {
    { ' ', '/', '\\', ' ' },
    { '<', 'O', 'O', '>' },
    { ' ', '\\', '/', ' ' }
  };
  setAppearance(appearance);
  setWidth(appearance[0].size());
  setHeight(appearance.size());
  setHealth(1);
}

void Enemy::takeDamage(unsigned int damage)
{
  if (getHealth() <= damage)
    setHealth(0);
  else
    setHealth(getHealth() - damage);
}