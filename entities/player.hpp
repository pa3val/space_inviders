#pragma once
#include "bullet.hpp"
#include "constants.hpp"
#include "damageable.hpp"
#include "entity.hpp"
#include "shooter.hpp"

#include <memory>


class Player : public Entity, public Shooter, public Damageable
{
public:
  Player();
  virtual ~Player() = default;
  std::unique_ptr<Bullet> shoot() override;
};