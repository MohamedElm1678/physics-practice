#include "profile.h"

const double Profile::GetTime(bool ignore) {
  double delta_x = goal_.position - current_.position;
  double discrim =
      std::pow(current_.velocity, 2) + (2 * kMaxAcceleration * delta_x);
  double max_v = std::sqrt((kMaxAcceleration * std::pow(current_.velocity, 2)) +
                           2 * kMaxAcceleration * goal_.position *
                               kMaxAcceleration / 2 * kMaxAcceleration);
  bool triangle;
  double total_time;
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
      double accel_time = (kMaxVelocity - current_.velocity) / kMaxAcceleration;
      double accel_dist = .5 * kMaxVelocity * accel_time;

      double vel_dist = delta_x - (2 * accel_dist);
      double vel_time = vel_dist / kMaxVelocity;

      total_time = (2 * accel_time) + vel_time;
      triangle = false;

      return total_time;
      // store in mem vars
      t1_ = accel_time;
      t2_ = accel_time + vel_time;
      t3_ = 0.0;
    } else if (max_v < kMaxVelocity) {
      double total_time = std::sqrt((2 * delta_x) / (kMaxAcceleration + 1.0));

      triangle = true;
      return total_time;
      // store in mem vars
      t1_ = total_time / 2;
      t3_ = total_time;
      t2_ = 0.0;
    }
  }
  triangle_ = triangle;
}

const Profile::ProfilePoint Profile::GetSetpoint(double time) {
  ProfilePoint calculated_point;
 // calculated_point.GetTime(false);
  // velocities
  double velocity, position;
  if (!triangle_) {
    if (time <= t1_) {
      velocity = current_.velocity + (time * kMaxAcceleration);
      position = (current_.velocity * t1_) +
                 (.5 * kMaxAcceleration * std::pow(t1_, 2));
    } else if (time >= t1_ && time <= (t1_ + t2_)) {
      velocity = kMaxVelocity;
      position =
          ((current_.velocity * t1_) +
           (.5 * kMaxAcceleration * std::pow(t1_, 2))) +
          ((kMaxVelocity * t2_) + (.5 * kMaxAcceleration * std::pow(t2_, 2)));

    } else if (time >= (t1_ + t2_)) {
      velocity = kMaxVelocity + (time * -kMaxAcceleration);
      position =
          ((current_.velocity * t1_) +
           (.5 * kMaxAcceleration * std::pow(t1_, 2))) +
          ((kMaxVelocity * t2_) + (.5 * kMaxAcceleration * std::pow(t2_, 2))) +
          ((kMaxVelocity * t3_) + (.5 * kMaxAcceleration * std::pow(t3_, 2)));
    } else {
      if (time <= t1_) {
        velocity = current_.velocity + (time * kMaxAcceleration);
        position = (current_.velocity * t1_) +
                   (.5 * kMaxAcceleration * std::pow(t1_, 2));
      } else if (time >= t3_) {
        double max_v =
            std::sqrt((kMaxAcceleration * std::pow(current_.velocity, 2)) +
                      2 * kMaxAcceleration * goal_.position * kMaxAcceleration /
                          2 * kMaxAcceleration);
        velocity = max_v + (time * -kMaxAcceleration);
        position = (current_.velocity * t3_) +
                   (.5 * kMaxAcceleration * std::pow(t3_, 2));
      }
    }

    calculated_point.velocity = velocity;
    calculated_point.position = position;
  }
  return calculated_point;
}
