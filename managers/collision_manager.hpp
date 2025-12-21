#pragma once
#include "entity.hpp"

class CollisionManager
{
public:
  static bool checkBounderCollision(const Entity& entity, short delta_x, short delta_y);
  static bool checkCollision(const Entity& entity1, const Entity& entity2);
};