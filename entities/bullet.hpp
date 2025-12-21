#pragma once
#include "entity.hpp"

class Bullet : public Entity
{
private:
  short        direction = 0;
  unsigned int damage    = 1;

public:
  Bullet(int p_x, int p_y, short direction);
  void         update();
  short        getDirection() const { return direction; }
  unsigned int getDamage() const { return damage; }
};