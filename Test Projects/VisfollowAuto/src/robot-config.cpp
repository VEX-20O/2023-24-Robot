#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor DriveL1 = motor(PORT1, ratio6_1, true);
motor DriveL2 = motor(PORT2, ratio6_1, true);
motor DriveL3 = motor(PORT3, ratio6_1, true);
motor DriveR1 = motor(PORT9, ratio6_1, false);
motor DriveR2 = motor(PORT8, ratio6_1, false);
motor DriveR3 = motor(PORT10, ratio6_1, false);
inertial Inertial6 = inertial(PORT6);
controller Controller1 = controller(primary);
digital_out Wings = digital_out(Brain.ThreeWirePort.H);
motor PunchMotor = motor(PORT5, ratio18_1, false);
digital_out Climb = digital_out(Brain.ThreeWirePort.G);
motor IntakeMotorA = motor(PORT4, ratio18_1, true);
motor IntakeMotorB = motor(PORT7, ratio18_1, false);
motor_group Intake = motor_group(IntakeMotorA, IntakeMotorB);
/*vex-vision-config:begin*/
signature Vision21__GO = signature (1, -7169, -4865, -6018, -6847, -4991, -5918, 2.5, 0);
vision Vision21 = vision (PORT21, 71, Vision21__GO);
/*vex-vision-config:end*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}