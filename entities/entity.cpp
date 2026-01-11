#include "entity.hpp"

Entity::Entity()
{
  pos_x_ = 0;
  pos_y_ = 0;
}

void Entity::update(const short delta_x, const short delta_y)
{
  pos_x_ += delta_x;
  pos_y_ += delta_y;
}