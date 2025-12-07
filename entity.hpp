#pragma once
#include <cstdlib>
#include <ncurses.h>
#include <vector>

class Entity
{
private:
  unsigned int                   width = 0, height = 0;
  int                            field_size_x = 0, field_size_y = 0;
  int                            pos_x = 0, pos_y = 0;
  unsigned short                 border_size = 0;
  std::vector<std::vector<char>> appearance;

public:
  Entity();
  Entity(int f_s_x, int f_s_y, unsigned int b_s);
  void drawObj();
  void update(short delta_x, short delta_y);

  int          getPosX() { return pos_x; }
  int          getPosY() { return pos_y; }
  unsigned int getHeight() { return height; }
  unsigned int getWidth() { return width; }
};