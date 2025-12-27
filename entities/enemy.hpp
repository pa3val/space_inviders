#pragma once
#include "damageable.hpp"
#include "entity.hpp"

class Enemy : public Entity, public Damageable
{
public:
  Enemy();
  Enemy(int pos_x, int pos_y);
  void takeDamage(unsigned int damage) override;
};