#pragma once
#include "bullet.hpp"
#include "collision_manager.hpp"
#include "constants.hpp"
#include "enemy.hpp"
#include "game_state.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "signal_manager.hpp"

#include <memory>
#include <vector>

class LevelState : public GameState
{
private:
  std::vector<std::unique_ptr<Bullet>> bullet_pool_;
  std::vector<std::unique_ptr<Enemy>>  enemy_pool_;
  Player                               player_;

public:
  LevelState();
  void createEnemies();
  void handleInput(Input input) override;
  void update() override;
  void draw() override;
  void drawField();
  void drawBullets();
  void drawEnemies();
};