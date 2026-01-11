#include "damageable.hpp"

void Damageable::takeDamage(const unsigned int damage)
{
  if (getHealth() <= damage)
    setHealth(0);
  else
    setHealth(getHealth() - damage);
}