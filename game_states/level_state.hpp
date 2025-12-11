#pragma once
#include "bullet.hpp"
#include "collision_manager.hpp"
#include "constants.hpp"
#include "game_state.hpp"
#include "input_manager.hpp"
#include "player.hpp"

#include <memory>
#include <vector>

class LevelState : public GameState
{
private:
  std::vector<std::unique_ptr<Bullet>> bullet_pool_;
  Player                               player_;
  CollisionManager                     collision_manager_;

public:
  LevelState();
  void handleInput(InputManager::Input input) override;
  void update() override { };
  void draw(const Renderer& renderer) override;
  void drawField(const Renderer& renderer);
};