#pragma once
#include "bullet.hpp"
#include "shooter.hpp"

#include <memory>

class Player : public Shooter
{
public:
  Player();
  std::unique_ptr<Bullet> shoot() override;
};