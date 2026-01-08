#pragma once
#include "basic_enemy.hpp"
#include "constants.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "shooter_enemy.hpp"

#include <filesystem>
#include <fstream>
#include <memory>
#include <sol/sol.hpp>
#include <vector>


class LevelManager
{
private:
  static std::string                                      level_file_;
  static std::vector<std::vector<std::unique_ptr<Enemy>>> enemy_pool_;
  static Player                                           player_;
  static BasicEnemy                                       basic_enemy_;
  static ShooterEnemy                                     shooter_enemy_;
  static int                                              enemy_shoot_chance_;
  static sol::state                                       lua_;

  static void setupPlayer();
  static void setupBasicEnemy();
  static void setupShooterEnemy();

public:
  static void readLevelFile();
  static void saveLevelFile();
  static void setLevelFile(const std::string& file_name)
  {
    level_file_ = file_name;
  }
  static std::string                                      getLevelFile() { return level_file_; }
  static std::string                                      getLevelFileName() { return std::filesystem::path(level_file_).stem().string(); }
  static std::vector<std::vector<std::unique_ptr<Enemy>>> takeEnemyPool() { return std::move(enemy_pool_); }
  static Player                                           takePlayer() { return player_; }
  static int                                              getShootChance() { return enemy_shoot_chance_; }
};
