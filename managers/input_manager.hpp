#pragma once
#include <ncurses.h>

class InputManager
{
public:
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

  Input getInputState();
};