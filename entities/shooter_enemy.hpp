#pragma once

#include "bullet.hpp"
#include "enemy.hpp"
#include "shooter.hpp"

#include <memory>

class ShooterEnemy : public Enemy, public Shooter
{
public:
  ShooterEnemy();
  virtual ~ShooterEnemy() = default;
  std::unique_ptr<Bullet> shoot() override;
};