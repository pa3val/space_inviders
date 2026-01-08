#pragma once
#include "entity.hpp"

#include <string>

class Bullet : public Entity
{
public:
  enum class BulletDirection
  {
    UP   = -1,
    DOWN = 1,
  };

private:
  BulletDirection direction_;
  unsigned int    damage_ = 1;

public:
  Bullet(int                                p_x,
      int                                   p_y,
      BulletDirection                       direction,
      unsigned short                        color_pair,
      const std::vector<std::vector<char>>& appearance);

  virtual ~Bullet() = default;
  void            update(short delta_x = 0, short delta_y = 0) override;
  BulletDirection getDirection() const { return direction_; }
  unsigned int    getDamage() const { return damage_; }
};