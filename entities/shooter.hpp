#pragma once
#include "bullet.hpp"
#include "entity.hpp"

#include <chrono>
#include <memory>

class Shooter : public Entity
{
private:
  unsigned int reload_time_ = 500;
  std::chrono::milliseconds::rep shoot_time_ = 0;

public:
  Shooter();
  virtual std::unique_ptr<Bullet> shoot() = 0;
  bool                            canShoot() const;
  void setShootTime(std::chrono::milliseconds::rep shoot_time) { shoot_time_ = shoot_time; }
};