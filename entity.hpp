#pragma once
#include <ncurses.h>
#include <vector>

class Entity
{
private:
  unsigned int                   _width = 0, _height = 0;
  int                            _pos_x = 0, _pos_y = 0;
  std::vector<std::vector<char>> _appearance = {
    { '/', '|', '|', '\\' },
    { '|', '0', '0', '|' },
    { ' ', '|', '|', ' ' }
  };
  ;

public:
  Entity();
  Entity(int p_x, int p_y);
  void         drawObj();
  virtual void update(short delta_x, short delta_y);
  int          getPosX() { return _pos_x; }
  int          getPosY() { return _pos_y; }
  unsigned int getHeight() { return _height; }
  unsigned int getWidth() { return _width; }
  void         setPosX(int pos_x) { _pos_x = pos_x; }
  void         setPosY(int pos_y) { _pos_y = pos_y; }
  void         setWidth(unsigned int width) { _width = width; }
  void         setHeight(unsigned int height) { _height = height; }
  void         setAppearance(const std::vector<std::vector<char>>& appearance)
  {
    _appearance = appearance;
  }
};