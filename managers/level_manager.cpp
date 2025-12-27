#include "level_manager.hpp"

std::vector<std::unique_ptr<Enemy>> LevelManager::enemy_pool_ = {};
Player                              LevelManager::player_     = Player();
std::string                         LevelManager::level_file_ = "";

void LevelManager::readLevelFile()
{
  enemy_pool_.clear();
  player_ = Player();

  std::ifstream file("levels/" + level_file_ + ".txt");
  if (!file.is_open())
  {
    throw std::runtime_error("Failed to open level file");
  }

  int  i = 0, j = 0;
  char ch;
  while (file.get(ch))
  {
    switch (ch)
    {
    case 'P':
      player_ = Player(i, j);
      break;
    case 'E':
      enemy_pool_.push_back(
          std::make_unique<Enemy>(
              Enemy(i + BORDER_SIZE, j + BORDER_SIZE)));
      break;
    case '\n':
      ++j;
      i = 0;
      continue;
    default:
      break;
    }
    ++i;
  }
  file.close();
}