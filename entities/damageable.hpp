class Damageable
{
private:
  unsigned int health_;

public:
  virtual void takeDamage(unsigned int damage) = 0;
  void         setHealth(unsigned int health) { health_ = health; }
  unsigned int getHealth() const { return health_; }
  bool         isAlive() const { return health_ > 0; }
};