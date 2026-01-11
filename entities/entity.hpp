#pragma once

#include "animator.hpp"

#include <vector>

class Entity
{
private:
  unsigned int                   width_ = 0, height_ = 0;
  int                            pos_x_ = 0, pos_y_ = 0;
  std::vector<std::vector<char>> appearance_;
  unsigned short                 color_pair_;

public:
  Animator animator_;

  Entity();
  virtual ~Entity() = default;
  virtual void                          update(const short delta_x, const short delta_y);
  int                                   getPosX() const { return pos_x_; }
  int                                   getPosY() const { return pos_y_; }
  unsigned int                          getHeight() const { return height_; }
  unsigned int                          getWidth() const { return width_; }
  const std::vector<std::vector<char>>& getAppearance() const { return appearance_; }
  unsigned short                        getColorPair() const { return color_pair_; }
  void                                  setPosX(const int pos_x) { pos_x_ = pos_x; }
  void                                  setPosY(const int pos_y) { pos_y_ = pos_y; }
  void                                  setWidth(const unsigned int width) { width_ = width; }
  void                                  setHeight(const unsigned int height) { height_ = height; }
  void                                  setAppearance(const std::vector<std::vector<char>>& appearance)
  {
    appearance_ = appearance;
  }
  void setColor(const unsigned short color_pair) { color_pair_ = color_pair; }
};