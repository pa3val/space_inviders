#include "renderer.hpp"

Renderer::Renderer(WINDOW* window)
    : window_(window)
{
}

void Renderer::draw_char(int x, int y, char ch, ColorPair color_pair) const
{
  int color = static_cast<int>(color_pair);
  attron(COLOR_PAIR(color));
  mvaddch(y, x, ch);
  attroff(COLOR_PAIR(color));
}

void Renderer::refresh_screen()
{
  refresh();
}

void Renderer::clear_screen()
{
  clear();
}

void Renderer::wait(int millis)
{
  napms(millis);
}