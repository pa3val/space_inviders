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
  setScore(0);
}