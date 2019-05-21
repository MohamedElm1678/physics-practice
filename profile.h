#ifndef PROFILE_H_
#define PROFILE_H_

#include <math.h>

constexpr double kMaxVelocity = 1.0;
constexpr double kMaxAcceleration = 1.0;

class Profile {

 public:
  struct ProfilePoint {
    double position = 0.0;
    double velocity = 0.0;
  };
 
  Profile(ProfilePoint current) {
    current_ = current;
  }
  
  void SetGoal(ProfilePoint goal) {
    goal_ = goal;
  }
  
  const double GetTime(bool ignore);

private:
  ProfilePoint current_, goal_;
};

#endif // PROFILE_H_
