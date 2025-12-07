#pragma once

#include "entity.hpp"

#include <cstdlib>
#include <ncurses.h>

class GameManager
{
private:
  int            height = 0, width = 0;
  unsigned short border_size = 1;
  Entity         player;

public:
  GameManager();
  void initScreen();
  void initColors();
  void runGame();
  void render();
  void drawField();
};