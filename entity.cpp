#include "entity.hpp"

Entity::Entity()
    : _pos_x(0)
    , _pos_y(0)
{
}

Entity::Entity(int p_x, int p_y)
    : _pos_x(p_x)
    , _pos_y(0)
{
  _width  = _appearance[0].size();
  _height = _appearance.size();
  _pos_y  = p_y - _height;
}

void Entity::drawObj()
{
  for (std::size_t i = 0; i < _height; ++i)
  {
    for (std::size_t j = 0; j < _width; ++j)
      mvaddch(i + _pos_y, j + _pos_x, _appearance[i][j]);
  }
}

void Entity::update(short delta_x, short delta_y)
{
  _pos_x += delta_x;
  _pos_y += delta_y;
}