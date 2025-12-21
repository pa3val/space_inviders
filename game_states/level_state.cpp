#include "level_state.hpp"

#include "collision_manager.hpp"
#include "renderer.hpp"

LevelState::LevelState()
{
  createEnemies();
}

void LevelState::createEnemies()
{
  for (int i = 0; i < 10; ++i)
  {
    Enemy enemy;
    enemy.setPosX(i * enemy.getWidth() + BORDER_SIZE);
    enemy.setPosY(BORDER_SIZE);
    enemy_pool_.push_back(std::make_unique<Enemy>(enemy));
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
  // НУЖНО ОПТИМИЗИРОВАТЬ!!!!!!!!!
  for (auto enemy = enemy_pool_.begin(); enemy != enemy_pool_.end();)
  {
    for (auto bullet = bullet_pool_.begin(); bullet != bullet_pool_.end();)
    {
      if (CollisionManager::checkCollision(**bullet, **enemy))
      {
        (*enemy)->takeDamage((*bullet)->getDamage());
        bullet = bullet_pool_.erase(bullet);
        if (!(*enemy)->isAlive())
        {
          enemy = enemy_pool_.erase(enemy);
          goto next_enemy; // исправить
        }
      }
      else
      {
        ++bullet;
      }
    }
    ++enemy;
  next_enemy:;
  }

  for (auto bullet = bullet_pool_.begin(); bullet != bullet_pool_.end();)
  {
    if (CollisionManager::checkBounderCollision(**bullet, 0, (*bullet)->getDirection()))
    {
      bullet = bullet_pool_.erase(bullet);
    }
    else
    {
      (*bullet)->update();
      ++bullet;
    }
  }
}

void LevelState::draw()
{
  drawField();
  Renderer::draw_entity(player_, ColorPair::PLAYER_COLOR);
  drawBullets();
  drawEnemies();
}

void LevelState::drawField()
{
  for (int i = 0; i < WIDTH; ++i)
  {
    for (unsigned short j = 0; j < BORDER_SIZE; ++j)
    {
      Renderer::draw_char(i, j, '-', ColorPair::BORDER_COLOR);
      Renderer::draw_char(i, HEIGHT - 1 - j, '-', ColorPair::BORDER_COLOR);
    }
  }
  for (int i = 1; i < HEIGHT - 1; ++i)
  {
    for (unsigned short j = 0; j < BORDER_SIZE; ++j)
    {
      Renderer::draw_char(j, i, '|', ColorPair::BORDER_COLOR);
      Renderer::draw_char(WIDTH - 1 - j, i, '|', ColorPair::BORDER_COLOR);
    }
  }
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