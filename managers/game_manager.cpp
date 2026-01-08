#include "game_manager.hpp"

#include "change_level_state.hpp"

#include <memory>

GameManager::GameManager()
{
  Renderer::initScreen();
  Renderer::initColorMap();
  AudioManager::initSounds();
  state_ = std::make_unique<MenuState>();
}

void GameManager::runGame()
{
  while (SignalManager::getSignal() != Signals::EXIT)
  {
    handleSignal();
    Input input = InputManager::getInputState();
    state_->handleInput(input);
    state_->update();
    Renderer::resetFlags();
    state_->draw();
    if ((SignalManager::getDrawFlags() & SignalManager::DrawFlags::DRAW_INFO_BAR)
        != SignalManager::DrawFlags::DRAW_NONE)
      Renderer::refreshWindow(Renderer::WindowType::INFO_BAR);
    if ((SignalManager::getDrawFlags() & SignalManager::DrawFlags::DRAW_PLAYFIELD)
        != SignalManager::DrawFlags::DRAW_NONE)
      Renderer::refreshWindow(Renderer::WindowType::PLAYFIELD);
    Renderer::updateScreen();
    SignalManager::clearDrawFlags();
    Renderer::wait(1000 / 30);
  }
  AudioManager::destroySounds();
  Renderer::exitGame();
}

void GameManager::handleSignal()
{
  switch (SignalManager::getSignal())
  {
  case Signals::START_GAME:
    state_ = std::make_unique<LevelState>();
    setupLevelQueue(LevelManager::getLevelFileName());
    SignalManager::setSignal(Signals::NONE);
    break;
  case Signals::CHANGE_TO_NEXT_LEVEL:
  {
    unsigned long score = 0;
    if (auto* change_level = dynamic_cast<ChangeLevelState*>(state_.get()))
    {
      if (change_level->getShowTime() > 0)
        return;
      else
        score = change_level->getScore();
    }
    AudioManager::stopBackgroundMusic();
    auto level_state = std::make_unique<LevelState>();
    level_state->setScore(score);
    state_ = std::move(level_state);
    SignalManager::setSignal(Signals::NONE);
    break;
  }
  case Signals::CHANGE_TO_MENU:
    AudioManager::stopBackgroundMusic();
    state_ = std::make_unique<MenuState>();
    SignalManager::setSignal(Signals::NONE);
    break;
  case Signals::GAME_WIN:
  {
    std::string next_level = "";
    if (!level_queue_.empty())
    {
      next_level = level_queue_.front();
      level_queue_.pop();
      LevelManager::setLevelFile(next_level);
      SignalManager::setSignal(Signals::CHANGE_TO_NEXT_LEVEL);
      unsigned long score = 0;
      if (auto* level = dynamic_cast<LevelState*>(state_.get()))
      {
        score = level->getScore();
      }
      state_ = std::make_unique<ChangeLevelState>(
          score,
          next_level,
          lua_["global_states"]["change_level_show_time"].get<unsigned short>());
      return;
    }
  }
  case Signals::GAME_OVER:
  {
    AudioManager::stopBackgroundMusic();
    unsigned long score = 0;
    if (auto* level = dynamic_cast<LevelState*>(state_.get()))
    {
      score = level->getScore();
    }
    state_ = std::make_unique<GameOverState>(score);
    SignalManager::setSignal(Signals::NONE);
    break;
  }
  default:
    break;
  }
}

void GameManager::setupLevelQueue(std::string first_level)
{
  level_queue_ = std::queue<std::string>();
  lua_.open_libraries(sol::lib::base, sol::lib::package);
  lua_.script_file("global_config.lua");
  sol::table levels         = lua_["levels_queue"];
  bool       is_level_found = false;

  for (auto& level_queue : levels)
  {
    sol::table level_queue_table = level_queue.second.as<sol::table>();
    for (auto& level : level_queue_table)
    {
      std::string level_name = level.second.as<std::string>();
      if (level_name == first_level)
      {
        is_level_found = true;
        continue;
      }
      if (is_level_found)
      {
        level_queue_.push(level_name);
      }
    }
    if (is_level_found)
      break;
  }
}