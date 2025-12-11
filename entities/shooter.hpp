#pragma once
#include "bullet.hpp"
#include "entity.hpp"

#include <memory>

class Shooter : public Entity
{
public:
  Shooter();
  virtual std::unique_ptr<Bullet> shoot() = 0;
};