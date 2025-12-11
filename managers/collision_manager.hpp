#pragma once
#include "entity.hpp"

#include <memory>

class CollisionManager
{
public:
  enum class CollisionType
  {
    ENTITY_ENTITY,
    ENTITY_BULLET,
    ENTITY_BORDER,
    NONE
  };

  CollisionManager();
  CollisionType checkCollision(const std::unique_ptr<Entity> f_entity,
      const std::unique_ptr<Entity>                          s_entity = nullptr);
};