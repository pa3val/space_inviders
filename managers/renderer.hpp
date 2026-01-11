#pragma once
#include "constants.hpp"
#include "entity.hpp"
#include "signal_manager.hpp"

#include <algorithm>
#include <curses.h>
#include <map>
#include <sol/sol.hpp>
#include <string>
#include <vector>
#include <windows.h>

class Renderer
{
private:
  static WINDOW*                                         playfield;
  static WINDOW*                                         info_bar;
  static bool                                            is_playfield_cleared;
  static bool                                            is_info_bar_cleared;
  static std::unordered_map<std::string, unsigned short> color_map_;
  struct RGBColor
  {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
  };

public:
  enum class WindowType
  {
    PLAYFIELD,
    INFO_BAR
  };

  static void           initScreen();
  static void           initPlayfield();
  static void           initInfoBar();
  static void           initColorMap();
  static void           resetFlags();
  static void           drawChar(const int x, const int y, const char ch, const WindowType window_type);
  static void           drawText(const int x, const int y, const std::string& text, const bool is_selected, const WindowType window_type);
  static void           drawEntity(const Entity& entity, const WindowType window_type);
  static void           clearWindow(const WindowType window_type);
  static void           refreshWindow(const WindowType window_type);
  static void           updateScreen();
  static void           wait(int millis);
  static void           destroyWindow(const WindowType window_type);
  static void           exitGame();
  static WINDOW*        getWindow(const WindowType window_type);
  static unsigned short getColor(const std::string& color_name) { return color_map_[color_name]; }
  static RGBColor       parseColorHex(std::string color_hex);
};