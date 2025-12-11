#pragma once
#include "constants.hpp"

#include <ncurses.h>

class Renderer
{
private:
  WINDOW* window_ = nullptr;

public:
  Renderer() { };
  Renderer(WINDOW* window);
  void draw_char(int x, int y, char ch, ColorPair color_pair) const;
  void clear_screen();
  void refresh_screen();
  void wait(int millis);
};