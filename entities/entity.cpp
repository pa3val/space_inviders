#include "entity.hpp"

Entity::Entity()
{
  pos_x_  = WIDTH / 2;
  pos_y_  = HEIGHT - BORDER_SIZE - height_;
}

void Entity::update(short delta_x, short delta_y)
{
  pos_x_ += delta_x;
  pos_y_ += delta_y;
}