#include "entity.hpp"

Entity::Entity()
    : field_size_x(0)
    , field_size_y(0)
    , border_size(0)
{
}

Entity::Entity(int f_s_x, int f_s_y, unsigned int b_s)
    : field_size_x(f_s_x)
    , field_size_y(f_s_y)
    , border_size(b_s)
{
  appearance = {
    { '/', '|', '|', '\\' },
    { '|', '0', '0', '|' },
    { ' ', '|', '|', ' ' }
  };
  width  = appearance[0].size();
  height = appearance.size();

  pos_x = field_size_x / 2;
  pos_y = field_size_y - border_size - height;
}

void Entity::drawObj()
{
  for (std::size_t i = 0; i < height; ++i)
  {
    for (std::size_t j = 0; j < width; ++j)
      mvaddch(i + pos_y, j + pos_x, appearance[i][j]);
  }
}

void Entity::update(short delta_x, short delta_y)
{
  if ((pos_x > border_size && delta_x < 0)
      || pos_x + width < field_size_x - border_size && delta_x > 0)
    pos_x += delta_x;
  if ((pos_y > border_size && delta_y < 0)
      || pos_y + height < field_size_y - border_size && delta_y > 0)
    pos_y += delta_y;
}