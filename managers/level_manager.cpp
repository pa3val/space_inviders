#include "level_manager.hpp"

std::vector<std::vector<std::unique_ptr<Enemy>>> LevelManager::enemy_pool_         = {};
Player                                           LevelManager::player_             = Player();
BasicEnemy                                       LevelManager::basic_enemy_        = BasicEnemy();
ShooterEnemy                                     LevelManager::shooter_enemy_      = ShooterEnemy();
std::string                                      LevelManager::level_file_         = "level_1";
int                                              LevelManager::enemy_shoot_chance_ = 5;
sol::state                                       LevelManager::lua_;

void LevelManager::readLevelFile()
{
  enemy_pool_.clear();
  lua_.open_libraries(sol::lib::base, sol::lib::package);
  lua_.script_file("global_config.lua");
  setupPlayer();
  setupBasicEnemy();
  setupShooterEnemy();
  enemy_shoot_chance_ = lua_["global_states"]["enemies"]["enemy_shoot_chance"].get<int>();

  std::ifstream file("levels/" + level_file_ + ".txt");
  if (!file.is_open())
  {
    throw std::runtime_error("Failed to open level file " + level_file_ + ".txt");
  }

  int                                 i = 0, j = 0;
  char                                ch;
  std::vector<std::unique_ptr<Enemy>> row;

  while (file.get(ch))
  {
    switch (ch)
    {
    case 'P':
      player_.setPosX(i);
      player_.setPosY(j);
      break;
    case 'B':
      basic_enemy_.setPosX(i);
      basic_enemy_.setPosY(j);
      row.push_back(
          std::make_unique<BasicEnemy>(
              basic_enemy_));
      break;
    case 'S':
      shooter_enemy_.setPosX(i);
      shooter_enemy_.setPosY(j);
      row.push_back(
          std::make_unique<ShooterEnemy>(
              shooter_enemy_));
      break;
    case '\n':
      ++j;
      i = 0;
      enemy_pool_.push_back(std::move(row));
      row.clear();
      continue;
    default:
      break;
    }
    ++i;
  }
  if (!row.empty())
    enemy_pool_.push_back(std::move(row));
  file.close();
}

void LevelManager::setupPlayer()
{
  sol::table player_states = lua_["global_states"]["player"];
  player_.setHealth(player_states["health"].get<unsigned int>());
  player_.setReloadFrameDelay(player_states["player_shoot_delay"].get<unsigned short>());
  player_.setAppearance(player_states["player_appearance"].get<std::vector<std::vector<char>>>());
  player_.setWidth(player_.getAppearance()[0].size());
  player_.setHeight(player_.getAppearance().size());
  player_.setBulletAppearance(player_states["player_bullet_appearance"].get<std::vector<std::vector<char>>>());
  player_.setColor(Renderer::getColor(player_states["color"].get<std::string>()));
  player_.setBulletColor(Renderer::getColor(player_states["bullet_color"].get<std::string>()));
}

void LevelManager::setupBasicEnemy()
{
  sol::table enemy_states = lua_["global_states"]["enemies"];
  basic_enemy_.setHealth(enemy_states["basic_enemy"]["health"].get<unsigned int>());
  basic_enemy_.setEnemyMovementDelay(enemy_states["enemy_movement_delay"].get<unsigned short>());
  basic_enemy_.setAppearance(enemy_states["basic_enemy"]["appearance"].get<std::vector<std::vector<char>>>());
  basic_enemy_.setWidth(basic_enemy_.getAppearance()[0].size());
  basic_enemy_.setHeight(basic_enemy_.getAppearance().size());
  basic_enemy_.setScore(enemy_states["basic_enemy"]["score"].get<unsigned long>());
  basic_enemy_.setColor(Renderer::getColor(enemy_states["basic_enemy"]["color"].get<std::string>()));
  basic_enemy_.animator_.setAnimationFrames(enemy_states["enemy_dead_animation"].get<std::vector<std::vector<std::vector<char>>>>());
  basic_enemy_.animator_.setFrameDelay(enemy_states["enemy_animation_frame_delay"].get<unsigned short>());
}

void LevelManager::setupShooterEnemy()
{
  sol::table enemy_states = lua_["global_states"]["enemies"];
  shooter_enemy_.setHealth(enemy_states["shooter_enemy"]["health"].get<unsigned int>());
  shooter_enemy_.setEnemyMovementDelay(enemy_states["enemy_movement_delay"].get<unsigned short>());
  shooter_enemy_.setReloadFrameDelay(enemy_states["shooter_enemy"]["enemy_shoot_delay"].get<unsigned short>());
  shooter_enemy_.setAppearance(enemy_states["shooter_enemy"]["appearance"].get<std::vector<std::vector<char>>>());
  shooter_enemy_.setWidth(shooter_enemy_.getAppearance()[0].size());
  shooter_enemy_.setHeight(shooter_enemy_.getAppearance().size());
  shooter_enemy_.setBulletAppearance(enemy_states["shooter_enemy"]["enemy_bullet_appearance"].get<std::vector<std::vector<char>>>());
  shooter_enemy_.setScore(enemy_states["shooter_enemy"]["score"].get<unsigned long>());
  shooter_enemy_.setColor(Renderer::getColor(enemy_states["shooter_enemy"]["color"].get<std::string>()));
  shooter_enemy_.setBulletColor(Renderer::getColor(enemy_states["shooter_enemy"]["bullet_color"].get<std::string>()));
  shooter_enemy_.animator_.setAnimationFrames(enemy_states["enemy_dead_animation"].get<std::vector<std::vector<std::vector<char>>>>());
  shooter_enemy_.animator_.setFrameDelay(enemy_states["enemy_animation_frame_delay"].get<unsigned short>());
}