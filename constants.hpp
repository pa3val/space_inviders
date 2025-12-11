#pragma once
#include <ncurses.h>

enum class ColorPair
{
  BORDER_COLOR = 1,
  PLAYER_COLOR,
  BULLET_COLOR
};

const int            HEIGHT = 25, WIDTH = 80;
const unsigned short BORDER_SIZE = 1;