#include "profile.h"
#include <iostream>
#include <fstream>
#include <string>

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
  

  std::ofstream outputFile("profile.csv");

  
  Profile::ProfilePoint calc_pt =  profile.GetSetpoint(.1);
  
  std::cout << calc_pt.velocity<< std::endl;
  for (double i = 0; i < 2.0; i+= .005 ){
  calc_pt =  profile.GetSetpoint(i);
	 outputFile << i << "," << calc_pt.position << "," << calc_pt.velocity << std::endl;
  }

}
