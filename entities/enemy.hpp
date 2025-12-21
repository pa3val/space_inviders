#pragma once
#include "damageable.hpp"
#include "entity.hpp"

class Enemy : public Entity, public Damageable
{
public:
  Enemy();
  void takeDamage(unsigned int damage) override;
};