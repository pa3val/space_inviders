#pragma once
#include "bullet.hpp"
#include "shooter.hpp"

#include <memory>

class Player : public Shooter
{
public:
  Player();
  Player(int pos_x, int pos_y);
  std::unique_ptr<Bullet> shoot() override;
};