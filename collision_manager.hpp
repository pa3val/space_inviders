#pragma once
#include "entity.hpp"

class CollisionManager
{
public:
  CollisionManager();
  CollisionManager(int f_s_x, int f_s_y, unsigned int b_s);
  bool checkBoundaryCollision(Entity& entity);
  bool canMove(Entity& entity, short delta_x, short delta_y);

private:
  int          field_size_x = 0;
  int          field_size_y = 0;
  unsigned int border_size  = 0;
};