#pragma once

#include "constants.hpp"
#include "game_state.hpp"
#include "renderer.hpp"

#include <string>

class ChangeLevelState : public GameState
{
private:
  unsigned long  score_ = 0;
  std::string    next_level_;
  unsigned short show_time_ = 0;

public:
  ChangeLevelState(const unsigned long score, const std::string& next_level, const unsigned short show_time);
  void           handleInput(Input input) override;
  void           update() override;
  void           draw() override;
  unsigned long  getScore() const { return score_; }
  unsigned short getShowTime() const { return show_time_; }
};