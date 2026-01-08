#include "level_state.hpp"

LevelState::LevelState()
{
  LevelManager::readLevelFile();
  enemy_pool_         = LevelManager::takeEnemyPool();
  player_             = LevelManager::takePlayer();
  enemy_shoot_chance_ = LevelManager::getShootChance();
  draw_flags_ |= SignalManager::DrawFlags::DRAW_PLAYFIELD;
  draw_flags_ |= SignalManager::DrawFlags::DRAW_INFO_BAR;
  AudioManager::playBackgroundMusic();
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
  case Input::FIRE:
    if (auto bullet = player_.shoot())
    {
      bullet_pool_.push_back(std::move(bullet));
      AudioManager::playSound("PLAYER_SHOOT_SOUND");
    }
    break;
  case Input::EXIT:
    SignalManager::setSignal(Signals::CHANGE_TO_MENU);
    return;
  default:
    break;
  }
  if (!CollisionManager::checkBounderCollision(player_, delta_x, delta_y))
  {
    player_.update(delta_x, delta_y);
    draw_flags_ |= SignalManager::DrawFlags::DRAW_PLAYFIELD;
  }
}

void LevelState::update()
{
  player_.updateReloadFrameDelay();
  for (auto& row : enemy_pool_)
  {
    for (auto& enemy : row)
    {
      if (auto shooter_enemy = dynamic_cast<ShooterEnemy*>(enemy.get()))
        shooter_enemy->updateReloadFrameDelay();
      enemy->updateCurrentEnemyMovementDelay();
      enemy->animator_.updateAnimation();
      if (CollisionManager::checkCollision(player_, *enemy))
      {
        SignalManager::setSignal(Signals::GAME_OVER);
        return;
      }
    }
  }
  for (auto bullet = bullet_pool_.begin(); bullet != bullet_pool_.end();)
  {
    if (!(*bullet))
    {
      ++bullet;
      continue;
    }
    bool is_bullet_hit = false;
    for (auto& row : enemy_pool_)
    {
      if (row.empty())
        continue;
      if ((*bullet)->getDirection() == Bullet::BulletDirection::DOWN)
        break;
      for (auto enemy = row.begin(); enemy != row.end(); ++enemy)
      {
        if (!(*enemy) || !(*enemy)->isAlive() || (*enemy)->animator_.isAnimationRunning())
          continue;
        if (CollisionManager::checkCollision(**bullet, **enemy))
        {
          (*enemy)->takeDamage((*bullet)->getDamage());
          bullet->reset();
          is_bullet_hit = true;
          if (!(*enemy)->isAlive())
          {
            (*enemy)->animator_.startAnimation();
            AudioManager::playSound("ENEMY_EXPLOSION_SOUND");
          }
          break;
        }
      }
      if (is_bullet_hit)
        break;
    }

    if (!is_bullet_hit
        && (*bullet)
        && (*bullet)->getDirection() == Bullet::BulletDirection::DOWN
        && CollisionManager::checkCollision(**bullet, player_))
    {
      player_.takeDamage((*bullet)->getDamage());
      if (!player_.isAlive())
      {
        SignalManager::setSignal(Signals::GAME_OVER);
        return;
      }
      bullet->reset();
      draw_flags_ |= SignalManager::DrawFlags::DRAW_INFO_BAR;
      break;
    }
    ++bullet;
  }

  bullet_pool_.erase(
      std::remove_if(bullet_pool_.begin(), bullet_pool_.end(),
          [this](const auto& bullet)
          {
            if (!bullet)
            {
              draw_flags_ |= SignalManager::DrawFlags::DRAW_PLAYFIELD;
              return true;
            }
            return (bullet->getPosY() < static_cast<int>(BORDER_SIZE)
                    || bullet->getPosY() > static_cast<int>(PLAYFIELD_HEIGHT - BORDER_SIZE));
          }),
      bullet_pool_.end());

  for (auto& row : enemy_pool_)
  {
    row.erase(
        std::remove_if(row.begin(), row.end(),
            [this](const auto& enemy)
            {
              if (!enemy->isAlive() && enemy->animator_.isAnimationFinished())
              {
                score_ += enemy->getScore();
                draw_flags_ |= SignalManager::DrawFlags::DRAW_INFO_BAR;
                draw_flags_ |= SignalManager::DrawFlags::DRAW_PLAYFIELD;
                return true;
              }
              return false;
            }),
        row.end());
  }

  enemy_pool_.erase(
      std::remove_if(enemy_pool_.begin(), enemy_pool_.end(),
          [](const auto& row)
          {
            return row.empty();
          }),
      enemy_pool_.end());

  if (enemy_pool_.empty())
  {
    SignalManager::setSignal(Signals::GAME_WIN);
    return;
  }

  moveEnemies();
  shootEnemies();

  for (auto& bullet : bullet_pool_)
  {
    bullet->update();
  }
  if (!bullet_pool_.empty())
    draw_flags_ |= SignalManager::DrawFlags::DRAW_PLAYFIELD;
}

void LevelState::moveEnemies()
{
  if (enemy_pool_.empty())
    return;
  short delta_y          = 0;
  bool  is_collided      = false;
  bool  is_ready_to_move = false;
  for (auto& row : enemy_pool_)
  {
    for (auto& enemy : row)
    {
      if (row.empty())
        continue;
      if (enemy->getCurrentEnemyMovementDelay() == 0)
      {
        is_ready_to_move = true;
        if (CollisionManager::checkBounderCollision(*enemy, enemy_direction_x_, 0))
        {
          is_collided = true;
          break;
        }
      }
    }
  }
  if (is_collided)
  {
    enemy_direction_x_ = -enemy_direction_x_;
    delta_y            = 1;
  }
  if (is_ready_to_move)
  {
    for (auto& row : enemy_pool_)
    {
      if (row.empty())
        continue;
      for (auto& enemy : row)
      {
        enemy->update(enemy_direction_x_, delta_y);
        enemy->resetCurrentEnemyMovementDelay();
      }
      draw_flags_ |= SignalManager::DrawFlags::DRAW_PLAYFIELD;
    }
  }
}

void LevelState::shootEnemies()
{
  if (enemy_pool_.empty())
    return;
  for (auto& row : enemy_pool_)
  {
    if (row.empty())
      continue;
    for (auto& enemy : row)
    {
      if (auto shooter_enemy = dynamic_cast<ShooterEnemy*>(enemy.get()))
      {
        if (chance(rng_) <= enemy_shoot_chance_ && shooter_enemy->canShoot())
        {
          bullet_pool_.push_back(shooter_enemy->shoot());
          AudioManager::playSound("ENEMY_SHOOT_SOUND");
        }
      }
    }
  }
}

void LevelState::draw()
{
  if ((draw_flags_ & SignalManager::DrawFlags::DRAW_PLAYFIELD) != SignalManager::DrawFlags::DRAW_NONE)
  {
    Renderer::drawEntity(player_, Renderer::WindowType::PLAYFIELD);
    drawEnemies();
    drawBullets();
  }
  if ((draw_flags_ & SignalManager::DrawFlags::DRAW_INFO_BAR) != SignalManager::DrawFlags::DRAW_NONE)
  {
    Renderer::drawText(1, 1, "Score: " + std::to_string(score_), false, Renderer::WindowType::INFO_BAR);
    Renderer::drawText(1, 2, "Health: " + std::to_string(player_.getHealth()), false, Renderer::WindowType::INFO_BAR);
  }
  draw_flags_ = SignalManager::DrawFlags::DRAW_NONE;
}

void LevelState::drawBullets()
{
  for (auto& bullet : bullet_pool_)
  {
    if (bullet)
      Renderer::drawEntity(*bullet, Renderer::WindowType::PLAYFIELD);
  }
}

void LevelState::drawEnemies()
{
  for (auto& row : enemy_pool_)
  {
    for (auto& enemy : row)
    {
      if (enemy)
        Renderer::drawEntity(*enemy, Renderer::WindowType::PLAYFIELD);
    }
  }
}
