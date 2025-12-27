#include "level_state.hpp"

LevelState::LevelState()
{
  lua.open_libraries(sol::lib::base, sol::lib::package);
  LevelManager::readLevelFile();
  setupLevel(LevelManager::getLevelFile());
  enemy_pool_ = LevelManager::takeEnemyPool();
  player_     = LevelManager::takePlayer();
}

void LevelState::setupLevel(const std::string& level_file)
{
  lua.script_file("config.lua");
  enemy_movement_delay = lua["global_state"]["enemy_delay"].get<unsigned short>();

  if (std::filesystem::exists("levels/" + level_file + ".lua"))
  {
    lua.script_file("levels/" + level_file + ".lua");
    enemy_movement_delay = lua["level_state"]["enemy_delay"].get<unsigned short>();
  }
}

void LevelState::handleInput(Input input)
{
  short delta_x = 0, delta_y = 0;

  switch (input)
  {
  case Input::MOVE_RIGHT:
    delta_x = 1;
    break;
  case Input::MOVE_LEFT:
    delta_x = -1;
    break;
  case Input::MOVE_UP:
    delta_y = -1;
    break;
  case Input::MOVE_DOWN:
    delta_y = 1;
    break;
  case Input::FIRE:
    if (auto bullet = player_.shoot())
      bullet_pool_.push_back(std::move(bullet));
    break;
  case Input::EXIT:
    SignalManager::setSignal(Signals::CHANGE_TO_MENU);
    return;
  }
  if (!CollisionManager::checkBounderCollision(player_, delta_x, delta_y))
    player_.update(delta_x, delta_y);
}

void LevelState::update()
{
  for (auto& enemy : enemy_pool_)
  {
    if (CollisionManager::checkCollision(player_, *enemy))
    {
      SignalManager::setSignal(Signals::GAME_OVER);
      return;
    }
  }

  for (auto bullet = bullet_pool_.begin(); bullet != bullet_pool_.end();)
  {
    for (auto enemy = enemy_pool_.begin(); enemy != enemy_pool_.end(); ++enemy)
    {
      if (CollisionManager::checkCollision(**bullet, **enemy))
      {
        (*enemy)->takeDamage((*bullet)->getDamage());
        bullet->reset();
        break;
      }
    }
    ++bullet;
  }

  bullet_pool_.erase(
      std::remove_if(bullet_pool_.begin(), bullet_pool_.end(),
          [](const auto& bullet)
          {
            if (!bullet)
              return true;
            return bullet->getPosY() < static_cast<int>(BORDER_SIZE);
          }),
      bullet_pool_.end());

  enemy_pool_.erase(
      std::remove_if(enemy_pool_.begin(), enemy_pool_.end(),
          [](const auto& enemy)
          {
            return !enemy->isAlive();
          }),
      enemy_pool_.end());

  for (auto& bullet : bullet_pool_)
  {
    bullet->update();
  }
  moveEnemies();
}

void LevelState::moveEnemies()
{
  ++current_enemy_movement_delay;
  if (current_enemy_movement_delay >= enemy_movement_delay)
  {
    current_enemy_movement_delay = 0;
    for (auto& enemy : enemy_pool_)
    {
      enemy->update(0, 1);
    }
  }
}

void LevelState::draw()
{
  Renderer::draw_entity(player_, ColorPair::PLAYER_COLOR);
  drawBullets();
  drawEnemies();
}

void LevelState::drawBullets()
{
  for (auto& bullet : bullet_pool_)
  {
    Renderer::draw_entity(*bullet, ColorPair::BULLET_COLOR);
  }
}

void LevelState::drawEnemies()
{
  for (auto& enemy : enemy_pool_)
  {
    Renderer::draw_entity(*enemy, ColorPair::ENEMY_COLOR);
  }
}