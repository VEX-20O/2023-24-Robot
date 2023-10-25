#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor DriveL1 = motor(PORT1, ratio18_1, false);
motor DriveL2 = motor(PORT2, ratio18_1, false);
motor DriveL3 = motor(PORT3, ratio18_1, false);
motor DriveR1 = motor(PORT4, ratio18_1, true);
motor DriveR2 = motor(PORT5, ratio18_1, true);
motor DriveR3 = motor(PORT6, ratio18_1, true);
inertial Inertial7 = inertial(PORT7);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}