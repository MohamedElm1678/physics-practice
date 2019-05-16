#ifndef PROFILE_H_
#define PROFILE_H_

#include <math.h>

struct Constraints {
  double kMaxVelocity = 1.0;
  double kMaxAcceleration = 1.0;
};

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
  Constraints constraints_;
  ProfilePoint current_, goal_;
};

#endif // PROFILE_H_
