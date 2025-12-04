#include "game_manager.hpp"

GameManager::GameManager()
{
  initScreen();
  initColors();
}

void GameManager::initScreen()
{
  initscr();
  start_color();
  nodelay(stdscr, TRUE);
  curs_set(0);
  getmaxyx(stdscr, height, width);
}

void GameManager::initColors()
{
  init_pair(1, COLOR_BLACK, COLOR_GREEN);
}

void GameManager::runGame()
{
  bool is_gameover = false;
  while(!is_gameover)
  {
    int key = getch();
    if (key == 27)
      is_gameover = true;

    render();
    napms(30);
  }
  curs_set(1);
  endwin();
}

void GameManager::render()
{
  clear();
  drawField();
  refresh();
}

void GameManager::drawField()
{
  attron(COLOR_PAIR(1));
  for (std::size_t i = 0; i < width; ++i)
  {
    mvaddch(0, i, '-');
    mvaddch(height - 1, i, '-');
  }
  for (std::size_t i = 1; i < height - 1; ++i)
  {
    mvaddch(i, 0, '|');
    mvaddch(i, width - 1, '|');
  }
  attroff(COLOR_PAIR(1));
}