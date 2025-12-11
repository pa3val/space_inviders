#pragma once
#include "input_manager.hpp"
#include "renderer.hpp"
class GameState
{
public:
  GameState() { };
  virtual void handleInput(InputManager::Input input) { };
  virtual void update() { };
  virtual void draw(const Renderer& renderer) { };
};