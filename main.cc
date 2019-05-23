#include "profile.h"
#include <iostream>

int main() {
  Profile::ProfilePoint current;
  Profile::ProfilePoint goal;
  {
    goal.position = 1.0;
    goal.velocity = 0.0;
  }

  Profile profile(current);
  profile.SetGoal(goal);



  std::cout << profile.GetTime(false) << std::endl;
  profile.GetSetpoint(.5);

  std::cout << current.velocity << std::endl;
}
