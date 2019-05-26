#include "profile.h"
#include <iostream>

int main() {
  Profile::ProfilePoint initial;
  Profile::ProfilePoint goal;
  {
    goal.position = 1.0;
    goal.velocity = 0.0;
  }

  Profile profile(initial);
  profile.SetGoal(goal);


  std::cout << profile.GetTime(false) << std::endl;
  Profile::ProfilePoint calc_pt =  profile.GetSetpoint(.5);
  
  std::cout << calc_pt.velocity << std::endl;
}
