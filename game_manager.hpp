#pragma once

#include "bullet.hpp"
#include "collision_manager.hpp"
#include "player.hpp"

#include <memory>
#include <ncurses.h>

class GameManager
{
private:
  int                                  height = 0, width = 0;
  unsigned short                       border_size = 1;
  std::vector<std::unique_ptr<Bullet>> bullet_pool;
  Player                               player;
  CollisionManager                     collision_manager;

public:
  GameManager();
  void initScreen();
  void initColors();
  void runGame();
  void drawBullets();
  void render();
  void drawField();

  template <typename Obj, typename Func>
  void handleInput(Obj& obj, int key, Func func)
  {
    switch (key)
    {
    case KEY_DOWN:
      if (collision_manager.canMove(obj, 0, 1))
        (obj.*func)(0, 1);
      break;
    case KEY_UP:
      if (collision_manager.canMove(obj, 0, -1))
        (obj.*func)(0, -1);
      break;
    case KEY_LEFT:
      if (collision_manager.canMove(obj, -1, 0))
        (obj.*func)(-1, 0);
      break;
    case KEY_RIGHT:
      if (collision_manager.canMove(obj, 1, 0))
        (obj.*func)(1, 0);
      break;
    case ' ':
      bullet_pool.push_back(player.shoot());
      break;
    }
  }
};