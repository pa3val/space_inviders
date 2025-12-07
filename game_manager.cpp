#include "game_manager.hpp"

GameManager::GameManager()
{
  initScreen();
  initColors();
  player = Entity(getmaxx(stdscr), getmaxy(stdscr), border_size);
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

void GameManager::initColors()
{
  init_pair(1, COLOR_BLACK, COLOR_GREEN);
}

template <typename Obj, typename Func>
void handleInput(Obj& obj, int key, Func func)
{
  switch (key)
  {
  case KEY_DOWN:
    (obj.*func)(0, 1);
    break;
  case KEY_UP:
    (obj.*func)(0, -1);
    break;
  case KEY_LEFT:
    (obj.*func)(-1, 0);
    break;
  case KEY_RIGHT:
    (obj.*func)(1, 0);
    break;
  }
}

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
  refresh();
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