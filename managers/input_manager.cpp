#include "input_manager.hpp"
#include "renderer.hpp"

#include <ncurses.h>

Input InputManager::getInputState()
{
  // Use game window for input
  int key = wgetch(Renderer::get_game_window());
  if (key == ERR)
    return Input::NONE;

  flushinp();

  switch (key)
  {
  case KEY_UP:
    return Input::MOVE_UP;
  case KEY_DOWN:
    return Input::MOVE_DOWN;
  case KEY_LEFT:
    return Input::MOVE_LEFT;
  case KEY_RIGHT:
    return Input::MOVE_RIGHT;
  case ' ':
    return Input::FIRE;
  case 27:
    return Input::EXIT;
  case '\n':
    return Input::SELECT;
  default:
    return Input::NONE;
  }
}