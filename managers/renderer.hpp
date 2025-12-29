#pragma once
#include "constants.hpp"
#include "entity.hpp"

#include <ncurses.h>
#include <string>

class Renderer
{
public:
  // Window management
  static void init_windows();
  static void destroy_windows();

  // Drawing to game window
  static void draw_char(int x, int y, char ch, ColorPair color_pair);
  static void draw_text(int x, int y, const std::string& text, ColorPair color_pair);
  static void draw_entity(const Entity& entity, ColorPair color_pair);

  // Drawing to info window
  static void draw_info_text(int x, int y, const std::string& text, ColorPair color_pair);

  static void clear_screen();
  static void refresh_screen();
  static void wait(int millis);
  static void exit_screen();

  static WINDOW* get_game_window();
  static WINDOW* get_info_window();

private:
  static WINDOW* game_win_;
  static WINDOW* info_win_;
};