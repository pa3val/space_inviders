#pragma once
#include "entity.hpp"

class Bullet : public Entity
{
private:
  short direction = 0;

public:
  Bullet(int p_x, int p_y, short direction);
  void update();
};