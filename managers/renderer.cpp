#include "renderer.hpp"

// Static member initialization
WINDOW* Renderer::game_win_ = nullptr;
WINDOW* Renderer::info_win_ = nullptr;

void Renderer::init_windows()
{
  // Create info window at the top
  info_win_ = newwin(INFO_WIN_HEIGHT, INFO_WIN_WIDTH, INFO_WIN_Y, INFO_WIN_X);
  // Create game window below the info window
  game_win_ = newwin(GAME_WIN_HEIGHT, GAME_WIN_WIDTH, GAME_WIN_Y, GAME_WIN_X);

  // Enable keypad for game window
  keypad(game_win_, TRUE);
}

void Renderer::destroy_windows()
{
  if (info_win_)
  {
    delwin(info_win_);
    info_win_ = nullptr;
  }
  if (game_win_)
  {
    delwin(game_win_);
    game_win_ = nullptr;
  }
}

WINDOW* Renderer::get_game_window()
{
  return game_win_;
}

WINDOW* Renderer::get_info_window()
{
  return info_win_;
}

void Renderer::draw_char(int x, int y, char ch, ColorPair color_pair)
{
  int color = static_cast<int>(color_pair);
  wattron(game_win_, COLOR_PAIR(color));
  mvwaddch(game_win_, y, x, ch);
  wattroff(game_win_, COLOR_PAIR(color));
}

void Renderer::draw_text(int x, int y, const std::string& text, ColorPair color_pair)
{
  int color = static_cast<int>(color_pair);
  wattron(game_win_, COLOR_PAIR(color));
  mvwprintw(game_win_, y, x, "%s", text.c_str());
  wattroff(game_win_, COLOR_PAIR(color));
}

void Renderer::draw_info_text(int x, int y, const std::string& text, ColorPair color_pair)
{
  int color = static_cast<int>(color_pair);
  wattron(info_win_, COLOR_PAIR(color));
  mvwprintw(info_win_, y, x, "%s", text.c_str());
  wattroff(info_win_, COLOR_PAIR(color));
}

void Renderer::draw_entity(const Entity& entity, ColorPair color_pair)
{
  int color = static_cast<int>(color_pair);
  wattron(game_win_, COLOR_PAIR(color));

  for (int i = 0; i < entity.getHeight(); ++i)
  {
    for (int j = 0; j < entity.getWidth(); ++j)
    {
      mvwaddch(game_win_,
          i + entity.getPosY(),
          j + entity.getPosX(),
          entity.getAppearance()[i][j]);
    }
  }
  wattroff(game_win_, COLOR_PAIR(color));
}

void Renderer::refresh_screen()
{
  // Draw borders for both windows
  wattron(info_win_, COLOR_PAIR(static_cast<int>(ColorPair::BORDER_COLOR)));
  box(info_win_, 0, 0);
  wattroff(info_win_, COLOR_PAIR(static_cast<int>(ColorPair::BORDER_COLOR)));

  wattron(game_win_, COLOR_PAIR(static_cast<int>(ColorPair::BORDER_COLOR)));
  box(game_win_, 0, 0);
  wattroff(game_win_, COLOR_PAIR(static_cast<int>(ColorPair::BORDER_COLOR)));

  // Refresh both windows
  wrefresh(info_win_);
  wrefresh(game_win_);
}

void Renderer::clear_screen()
{
  werase(info_win_);
  werase(game_win_);
}

void Renderer::wait(int millis)
{
  napms(millis);
}

void Renderer::exit_screen()
{
  destroy_windows();
  curs_set(1);
  endwin();
}