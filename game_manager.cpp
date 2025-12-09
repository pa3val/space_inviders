#include "game_manager.hpp"

GameManager::GameManager()
{
  initScreen();
  initColors();
  player            = Player(width / 2, height - border_size);
  collision_manager = CollisionManager(width, height, border_size);
}

void GameManager::initScreen()
{
  initscr();
  start_color();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
  getmaxyx(stdscr, height, width);
}

void GameManager::initColors() { init_pair(1, COLOR_BLACK, COLOR_GREEN); }

void GameManager::runGame()
{
  bool is_gameover = false;
  while (is_gameover == false)
  {
    int key = getch();

    if (key == 27)
      is_gameover = true;
    else if (key != ERR)
      handleInput(player, key, &Entity::update);
    flushinp();
    render();
    napms(50);
  }

  curs_set(1);
  endwin();
}

void GameManager::render()
{
  clear();
  drawField();
  player.drawObj();
  drawBullets();
  refresh();
}

void GameManager::drawBullets()
{
  for (auto bullet = bullet_pool.begin();
      bullet != bullet_pool.end();)
  {
    bullet->get()->update();
    if (collision_manager.checkBoundaryCollision(*(bullet->get())))
      bullet = bullet_pool.erase(bullet);
    else
    {
      bullet->get()->drawObj();
      ++bullet;
    }
  }
}

void GameManager::drawField()
{
  attron(COLOR_PAIR(1));
  for (int i = 0; i < width; ++i)
  {
    for (unsigned short j = 0; j < border_size; ++j)
    {
      mvaddch(j, i, '-');
      mvaddch(height - 1 - j, i, '-');
    }
  }
  for (int i = 1; i < height - 1; ++i)
  {
    for (unsigned short j = 0; j < border_size; ++j)
    {
      mvaddch(i, j, '|');
      mvaddch(i, width - 1 - j, '|');
    }
  }
  attroff(COLOR_PAIR(1));
}