#include "profile.h"

const double Profile::GetTime(bool ignore) {
  double delta_x = goal_.position - current_.position;
  double discrim = (current_.velocity * current_.velocity) + (2 * constraints_.kMaxAcceleration * delta_x);
  
  if (ignore) {  
    double full_send_time = (current_.velocity + sqrt(discrim)) / constraints_.kMaxAcceleration;
  //  double full_send_time = delta_x / (.5 * (goal_.velocity + current_.velocity));
  //  double full_send_time = (current_.velocity + sqrt(discrim)) / constraints_.kMaxAcceleration;
    return full_send_time;
 } else {
   // first part of trapezoid
   double accel_time = (constraints_.kMaxAcceleration - current_.velocity) / constraints_.kMaxAcceleration;
   double accel_dist = .5 * constraints_.kMaxVelocity * accel_time; 
   
   double vel_time = delta_x - (2 * accel_dist);

   double full_time = (2 * accel_time) + (vel_time / constraints_.kMaxVelocity); 

  // double accel_time = (current_.velocity + sqrt(discrim)) / constraints_.kMaxAcceleration;
  // double dist_2 = delta_x - (accel_time * 2 * constraints_.velocity);
  // double vel_time = dist_2 / (constraints_.kMaxVelocity);
  // double accel_time = constraints_.kMaxVelocity - current_.position / constraints_.kMaxAcceleration;
  // double straight_dist = sqrt((2 * delta_x) / constraints_.kMaxAcceleration);
  // double vel_time = straight_dist / (.5 * (goal_.velocity + current_.velocity));
  // double deccel_time = constraints_.kMaxVelocity - current_.position / constraints_.kMaxAcceleration;

   return full_time;
 }
}
