#include "collision_manager.hpp"

CollisionManager::CollisionManager()
{
}

CollisionManager::CollisionType CollisionManager::checkCollision(const std::unique_ptr<Entity> f_entity,
    const std::unique_ptr<Entity>                                                              s_entity)
{
  if (f_entity->getPosX() < static_cast<int>(BORDER_SIZE)
      || f_entity->getPosX() + static_cast<int>(f_entity->getWidth())
             > WIDTH - static_cast<int>(BORDER_SIZE)
      || f_entity->getPosY() < static_cast<int>(BORDER_SIZE)
      || f_entity->getPosY() + static_cast<int>(f_entity->getHeight())
             > HEIGHT - static_cast<int>(BORDER_SIZE))
  {
    return CollisionType::ENTITY_BORDER;
  }
  return CollisionType::NONE;
}