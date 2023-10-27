#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// DriveL1              motor         1               
// DriveL2              motor         2               
// DriveL3              motor         3               
// DriveR1              motor         9               
// DriveR2              motor         8               
// DriveR3              motor         10              
// Inertial6            inertial      6               
// Controller1          controller                    
// Wings                digital_out   H               
// PunchMotor           motor         5               
// Climb                digital_out   G               
// Intake               motor_group   4, 7            
// Vision21             vision        21              
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;

Drive chassis(
ZERO_TRACKER_ODOM,
//Left Motors:
motor_group(DriveL1,DriveL2,DriveL3),
//Right Motors:
motor_group(DriveR1,DriveR2,DriveR3),

//PORT NUMBER of inertial
PORT6,

//Wheel Dia
3.25,

//External ratio (in/out)
0.66,

//gyro 
360,

//ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//Leave this alone
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

3,

2.75,

//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
4,

1,

-2.75,

5.5

);

int current_auton_selection = 0;
bool auto_started = false;

void ToggleClimb();

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();

  while(auto_started == false){            //Changing the names below will only change their names on the
    Brain.Screen.clearScreen();            //brain screen for auton selection.
    switch(current_auton_selection){       //Tap the brain screen to cycle through autons.
      case 0:
        Brain.Screen.printAt(50, 50, "Opp Desc");
        break;
      case 1:
        Brain.Screen.printAt(50, 50, "Same Score");
        break;
      case 2:
        Brain.Screen.printAt(50, 50, "Turn Test");
        break;
      case 3:
        Brain.Screen.printAt(50, 50, "Swing Test");
        break;
      case 4:
        Brain.Screen.printAt(50, 50, "Odom Test");
        break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 4){
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){  
    case 0:
    SameSide_Score();
       //This is the default auton, if you don't select from the brain.
      break;        //Change these to be your own auton functions in order to use the auton selector.
    case 1:         //Tap the screen to cycle through autons.
      OppSide_Desc();
      break;
    case 2:
      turn_test();
      break;
    case 3:
      swing_test();
      break;
    case 4:
      odom_test();
      break;
 }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  chassis.set_coordinates(0,0,0);
  Controller1.ButtonX.pressed(ToggleClimb);
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //Replace this line with chassis.control_tank(); for tank drive 
    //or chassis.control_holonomic(); for holo drive.
    chassis.control_arcade();
    
    Controller1.Screen.print(chassis.get_X_position());
    Controller1.Screen.print(" ");
    Controller1.Screen.print(chassis.get_Y_position());
    Controller1.Screen.newLine();
    /////USER DRIVE CODE BEGIN////

    if(Controller1.ButtonR1.pressing()){
      PunchMotor.spin(reverse, 10.5, volt);
    }else{
      PunchMotor.stop();
    }

    //Intake Code
    if(Controller1.ButtonR2.pressing()){
      Intake.spin(forward,75,percent);
    }
    else if(Controller1.ButtonL2.pressing()){
      Intake.spin(reverse,100,percent);
    }
    else{
      Intake.stop();
    }
    
    //Pneumatic Wings
    if(Controller1.ButtonL1.pressing())
    {
      Wings.set(true);
      Intake.spin(reverse,100,percent);
    }
    else{
      Wings.set(false);
    }
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

void ToggleClimb(){
  Climb.set(!Climb.value());
}
