#pragma once

#include "game_state.hpp"
#include "input_manager.hpp"
#include "level_state.hpp"
#include "renderer.hpp"

#include <memory>
#include <ncurses.h>

class GameManager
{
private:
  Renderer     renderer;
  InputManager input_manager;
  LevelState   state;

public:
  GameManager();
  void initScreen();
  void initColors();
  void runGame();
};