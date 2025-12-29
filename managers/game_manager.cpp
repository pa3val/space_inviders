#include "game_manager.hpp"

GameManager::GameManager()
{
  initScreen();
  initColors();
  state_ = std::make_unique<MenuState>();
}

void GameManager::initScreen()
{
  printf("\033[8;%d;%dt", SCREEN_HEIGHT, SCREEN_WIDTH);
  fflush(stdout);
  initscr();
  resize_term(SCREEN_HEIGHT, SCREEN_WIDTH);
  start_color();
  curs_set(0);
  raw();
  noecho();

  // Initialize the two windows
  Renderer::init_windows();

  // Set nodelay on game window for non-blocking input
  nodelay(Renderer::get_game_window(), TRUE);
}

void GameManager::initColors()
{
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_CYAN, COLOR_BLACK);
  init_pair(4, COLOR_BLACK, COLOR_YELLOW);
  init_pair(5, COLOR_WHITE, COLOR_BLACK);
  init_pair(6, COLOR_BLACK, COLOR_WHITE);
}

void GameManager::runGame()
{
  while (SignalManager::getSignal() != Signals::EXIT)
  {
    handleSignal();
    Input input = InputManager::getInputState();
    state_->handleInput(input);
    state_->update();
    Renderer::clear_screen();
    state_->draw();
    Renderer::refresh_screen();
    Renderer::wait(1000 / 30);
  }
  Renderer::exit_screen();
}

void GameManager::handleSignal()
{
  switch (SignalManager::getSignal())
  {
  case Signals::CHANGE_TO_LEVEL:
    state_ = std::make_unique<LevelState>();
    SignalManager::setSignal(Signals::NONE);
    break;
  case Signals::CHANGE_TO_MENU:
    state_ = std::make_unique<MenuState>();
    SignalManager::setSignal(Signals::NONE);
    break;
  case Signals::GAME_OVER:
    state_ = std::make_unique<MenuState>();
    SignalManager::setSignal(Signals::NONE);
    break;
  default:
    break;
  }
}