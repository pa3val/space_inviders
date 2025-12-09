#pragma once
#include "bullet.hpp"
#include "entity.hpp"

#include <memory>

class Shooter : public Entity
{
public:
  Shooter();
  Shooter(int p_x, int p_y);
  virtual std::unique_ptr<Bullet> shoot() = 0;
};