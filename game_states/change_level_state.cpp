#include "change_level_state.hpp"

#include "constants.hpp"

ChangeLevelState::ChangeLevelState(unsigned long score, const std::string& next_level, unsigned short show_time)
    : score_(score)
    , next_level_(next_level)
    , show_time_(show_time)
{
}

void ChangeLevelState::handleInput(Input input)
{
}

void ChangeLevelState::update()
{
  if (show_time_ > 0)
    --show_time_;
}

void ChangeLevelState::draw()
{
  std::string change_level_text = "Changing level...";
  Renderer::drawText(INFO_BAR_WIDTH / 2 - change_level_text.length() / 2, 1, change_level_text, true, Renderer::WindowType::INFO_BAR);
  std::string score_text = "Score: " + std::to_string(score_);
  Renderer::drawText(PLAYFIELD_WIDTH / 2 - score_text.length() / 2, 1, score_text, false, Renderer::WindowType::PLAYFIELD);
  std::string next_level_text = "Next level: " + next_level_;
  Renderer::drawText(PLAYFIELD_WIDTH / 2 - next_level_text.length() / 2, 2, next_level_text, false, Renderer::WindowType::PLAYFIELD);
}