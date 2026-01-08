#pragma once

#include <vector>

class Animator
{
private:
  unsigned short                              frame_delay_           = 0;
  unsigned short                              current_frame_delay_   = 0;
  unsigned short                              current_frame_         = 0;
  bool                                        is_animation_running_  = false;
  bool                                        is_animation_finished_ = false;
  std::vector<std::vector<std::vector<char>>> animation_frames_;

public:
  Animator();
  void                                  startAnimation();
  void                                  updateAnimation();
  const std::vector<std::vector<char>>& getCurrentFrame() const { return animation_frames_[current_frame_]; }
  void                                  setFrameDelay(unsigned short frame_delay) { frame_delay_ = frame_delay; }
  void                                  setAnimationFrames(const std::vector<std::vector<std::vector<char>>> animation_frames) { animation_frames_ = animation_frames; }
  bool                                  isAnimationFinished() const { return is_animation_finished_; }
  bool                                  isAnimationRunning() const { return is_animation_running_; }
};