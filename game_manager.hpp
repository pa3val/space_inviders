#pragma once

#include <ncurses.h>
#include <cstdlib>

class GameManager
{
  private:
  int height = 0, width = 0;
  public:
  GameManager();
  void initScreen();
  void initColors();
  void runGame();
  void render();
  void drawField();
};