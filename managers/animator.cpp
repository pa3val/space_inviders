#include "animator.hpp"

Animator::Animator()
{
}

void Animator::startAnimation()
{
  if (is_animation_running_)
    return;
  is_animation_running_  = true;
  is_animation_finished_ = false;
  current_frame_delay_   = frame_delay_;
  current_frame_         = 0;
}

void Animator::updateAnimation()
{
  if (!is_animation_running_ || is_animation_finished_)
    return;
  current_frame_delay_--;
  if (current_frame_delay_ == 0)
  {
    current_frame_delay_ = frame_delay_;
    current_frame_++;
    if (current_frame_ >= animation_frames_.size())
      is_animation_finished_ = true;
  }
}
