package hello;

public class Greeter {
  public Double sayHello(boolean ignore, ProfilePoint current_, ProfilePoint goal_) {
    Constraints constraints_ = new Constraints();

    double delta_x = goal_.position - current_.position;
    double discrim = (current_.velocity * current_.velocity) + (2 * constraints_.kMaxAcceleration * delta_x);

    if (ignore) {
      double full_send_time = (current_.velocity + Math.sqrt(discrim)) / constraints_.kMaxAcceleration;
      return full_send_time;
    } else {
      // first part of trapezoid
      double accel_time = (goal_.velocity - current_.velocity) / constraints_.kMaxAcceleration;
      double accel_dist = .5 * constraints_.kMaxVelocity * accel_time;

      double vel_time = delta_x - (2 * accel_dist);

      double total_time = (2 * accel_time) + (vel_time / constraints_.kMaxVelocity);

      return total_time;
    }
  }
}
