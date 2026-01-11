#pragma once

#include "audio_manager.hpp"
#include "change_level_state.hpp"
#include "constants.hpp"
#include "game_over_state.hpp"
#include "game_state.hpp"
#include "input_manager.hpp"
#include "level_state.hpp"
#include "menu_state.hpp"
#include "renderer.hpp"
#include "signal_manager.hpp"

#include <memory>
#include <queue>
#include <sol/sol.hpp>

class GameManager
{
private:
  std::unique_ptr<GameState> state_ = std::make_unique<LevelState>();
  std::queue<std::string>    level_queue_;
  sol::state                 lua_;

public:
  GameManager();
  void runGame();
  void handleSignal();
  void setupLevelQueue(const std::string& first_level);
};