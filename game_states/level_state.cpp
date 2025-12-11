#include "level_state.hpp"

LevelState::LevelState()
{
}

void LevelState::handleInput(InputManager::Input input)
{
  using Input         = InputManager::Input;
  using CollisionType = CollisionManager::CollisionType;
  switch (input)
  {
  case Input::MOVE_RIGHT:
    if (collision_manager_.checkCollision(std::make_unique<Entity>(player_))
        == CollisionType::NONE)
      player_.update(1, 0);
    break;
  case Input::MOVE_LEFT:
    if (collision_manager_.checkCollision(std::make_unique<Entity>(player_))
        == CollisionType::NONE)
      player_.update(-1, 0);
    break;
  }
}

void LevelState::draw(const Renderer& renderer)
{
  drawField(renderer);
  std::vector<std::vector<char>> player_appearance = player_.getAppearance();
  for (int i = 0; i < player_.getHeight(); ++i)
  {
    for (int j = 0; j < player_.getWidth(); ++j)
      renderer.draw_char(j + player_.getPosX(),
          i + player_.getPosY(),
          player_appearance[i][j],
          ColorPair::PLAYER_COLOR);
  }
}

void LevelState::drawField(const Renderer& renderer)
{
  for (int i = 0; i < WIDTH; ++i)
  {
    for (unsigned short j = 0; j < BORDER_SIZE; ++j)
    {
      renderer.draw_char(i, j, '-', ColorPair::BORDER_COLOR);
      renderer.draw_char(i, HEIGHT - 1 - j, '-', ColorPair::BORDER_COLOR);
    }
  }
  for (int i = 1; i < HEIGHT - 1; ++i)
  {
    for (unsigned short j = 0; j < BORDER_SIZE; ++j)
    {
      renderer.draw_char(j, i, '|', ColorPair::BORDER_COLOR);
      renderer.draw_char(WIDTH - 1 - j, i, '|', ColorPair::BORDER_COLOR);
    }
  }
}