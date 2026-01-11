#pragma once

class Damageable
{
private:
  unsigned int health_ = 0;

public:
  virtual void takeDamage(const unsigned int damage);
  void         setHealth(const unsigned int health) { health_ = health; }
  unsigned int getHealth() const { return health_; }
  bool         isAlive() const { return health_ > 0; }
};