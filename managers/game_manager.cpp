#include "game_manager.hpp"

GameManager::GameManager()
{
  initScreen();
  initColors();
  renderer = Renderer(stdscr);
  state    = LevelState();
}

void GameManager::initScreen()
{
  initscr();
  start_color();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
}

void GameManager::initColors()
{
  init_pair(1, COLOR_BLACK, COLOR_GREEN);
  init_pair(1, COLOR_BLACK, COLOR_RED);
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
}

void GameManager::runGame()
{
  using Input = InputManager::Input;

  while (true)
  {
    Input input = input_manager.getInputState();
    state.handleInput(input);
    state.update();

    renderer.clear_screen();
    state.draw(renderer);
    renderer.refresh_screen();
    renderer.wait(50);
  }
}