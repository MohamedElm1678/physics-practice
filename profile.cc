#include "profile.h"

const double Profile::GetTime(bool ignore) {
  double delta_x = goal_.position - current_.position;
  double discrim = (current_.velocity * current_.velocity) +
                   (2 * kMaxAcceleration * delta_x);
  double max_v = std::sqrt((kMaxAcceleration * std::pow(current_.velocity, 2)) +
                           2 * kMaxAcceleration * goal_.position *
                               kMaxAcceleration / 2 * kMaxAcceleration);

  if (ignore) {
    double full_send_time =
        (current_.velocity + sqrt(discrim)) / kMaxAcceleration;
    //  double full_send_time = delta_x / (.5 * (goal_.velocity +
    //  current_.velocity)); double full_send_time = (current_.velocity +
    //  sqrt(discrim)) / kMaxAcceleration;
    return full_send_time;
  } else {
    if (max_v == kMaxVelocity) {
      // first part of trapezoid
      double accel_time =
          (goal_.velocity - current_.velocity) / kMaxAcceleration;
      double accel_dist = .5 * kMaxVelocity * accel_time;

      double vel_time = delta_x - (2 * accel_dist);

      double total_time = (2 * accel_time) + (vel_time / kMaxVelocity);

      return total_time;
    } else if (max_v < kMaxVelocity) {
      double total_time = std::sqrt((2 * delta_x) / (kMaxAcceleration + 1.0));
      return total_time;
    }
  }
}
