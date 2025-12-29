#pragma once
#include <ncurses.h>

enum class ColorPair
{
  ENEMY_COLOR = 1,
  PLAYER_COLOR,
  BORDER_COLOR,
  BULLET_COLOR,
  TEXT_COLOR,
  SELECTED_TEXT_COLOR
};

enum class Input
{
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  FIRE,
  PAUSE,
  EXIT,
  SELECT,
  NONE
};

enum class Signals
{
  EXIT,
  CHANGE_TO_LEVEL,
  CHANGE_TO_MENU,
  GAME_OVER,
  NONE
};

constexpr int SCREEN_HEIGHT = 30;
constexpr int SCREEN_WIDTH  = 80;

// Info window (top bar)
constexpr int INFO_WIN_HEIGHT = 3;
constexpr int INFO_WIN_WIDTH  = SCREEN_WIDTH;
constexpr int INFO_WIN_Y      = 0;
constexpr int INFO_WIN_X      = 0;

// Game window (main play area)
constexpr int GAME_WIN_HEIGHT = SCREEN_HEIGHT - INFO_WIN_HEIGHT;
constexpr int GAME_WIN_WIDTH  = SCREEN_WIDTH;
constexpr int GAME_WIN_Y      = INFO_WIN_HEIGHT;
constexpr int GAME_WIN_X      = 0;

// For backward compatibility
constexpr int HEIGHT                 = GAME_WIN_HEIGHT;
constexpr int WIDTH                  = GAME_WIN_WIDTH;
constexpr unsigned short BORDER_SIZE = 1;