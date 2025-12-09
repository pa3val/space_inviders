#include "collision_manager.hpp"

CollisionManager::CollisionManager()
    : field_size_x(0)
    , field_size_y(0)
    , border_size(0)
{
}

CollisionManager::CollisionManager(int f_s_x, int f_s_y, unsigned int b_s)
    : field_size_x(f_s_x)
    , field_size_y(f_s_y)
    , border_size(b_s)
{
}

bool CollisionManager::checkBoundaryCollision(Entity& entity)
{
  if (entity.getPosX() < static_cast<int>(border_size)
      || entity.getPosX() + static_cast<int>(entity.getWidth())
             > field_size_x - static_cast<int>(border_size)
      || entity.getPosY() < static_cast<int>(border_size)
      || entity.getPosY() + static_cast<int>(entity.getHeight())
             > field_size_y - static_cast<int>(border_size))
  {
    return true;
  }
  return false;
}

bool CollisionManager::canMove(Entity& entity, short delta_x, short delta_y)
{
  int new_x = entity.getPosX() + delta_x;
  int new_y = entity.getPosY() + delta_y;

  if (new_x < border_size
      || new_x + static_cast<int>(entity.getWidth())
             > field_size_x - static_cast<int>(border_size))
    return false;
  if (new_y < border_size
      || new_y + static_cast<int>(entity.getHeight())
             > field_size_y - static_cast<int>(border_size))
    return false;
  return true;
}