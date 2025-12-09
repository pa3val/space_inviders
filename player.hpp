#pragma once
#include "bullet.hpp"
#include "shooter.hpp"

#include <memory>

class Player : public Shooter
{
public:
  Player();
  Player(int p_x, int p_y);
  std::unique_ptr<Bullet> shoot() override;
};