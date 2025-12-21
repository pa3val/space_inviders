#include "shooter.hpp"

Shooter::Shooter()
    : Entity()
{
}

bool Shooter::canShoot() const
{
  return shoot_time_ + reload_time_ <= std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
                                           .count();
}