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

//External drive gear ratio (in/out)
0.66,

//gyro degrees
360,

//positive distance from the center of the robot to the right side of the drive
//This distance is in inches:
4
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
           Brain.Screen.printAt(50, 50, "SHILLS");
       
        break;
      case 1:
        Brain.Screen.printAt(50, 50, "Opposite Score Pre & Desc & Touch");
        break;
      case 2:
        Brain.Screen.printAt(50, 50, "DO NOTHING!");
        break;
      case 3:
        Brain.Screen.printAt(50, 50, "Desc & Opposite Shoot 2");
        break;
      case 4:
        Brain.Screen.printAt(50, 50, "Offensive Score 2 Touch");
        break;
      case 5:
        Brain.Screen.printAt(50, 50, "Opposite WP Descore & Launch Pre & Touch");
        break;
      case 6:
        Brain.Screen.printAt(50, 50, "Vision Test SameSide (HAVE ROBOT SETUP");
        break;
      case 7:
            Brain.Screen.printAt(50, 50, "Offensive Score 3");
      break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 8){
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){  
    case 0:
    
       OppSide_Desc_Mid();
       break;     
    case 1:        
      OppSide_Desc_Score_Score();
      break;
    case 2:
      Sit();
      break;
    case 3:
        Skills();
      break;
    case 4:
      SameSide_NoMid();
      break;
    case 5:
      Opp_WP();
      break;
    case 6:
      VisTest();
      break;
    case 7:
     SameSide_Score();
      break;
 }
}

void usercontrol(void) {
  chassis.set_coordinates(0,0,0);
  Controller1.ButtonX.pressed(ToggleClimb);
  // User control code here, inside the loop
  while (1) {
    //Replace this line with chassis.control_tank(); for tank drive 
    chassis.control_arcade();
    
    Controller1.Screen.print(chassis.get_X_position());
    Controller1.Screen.print(" ");
    Controller1.Screen.print(chassis.get_Y_position());
    Controller1.Screen.newLine();

    if(Controller1.ButtonR1.pressing()){
      PunchMotor.spin(reverse, 10.5, volt);
    }
    else{
      PunchMotor.stop();
    }

    //Intake Code
    if(Controller1.ButtonR2.pressing()){
      Intake.spin(forward,100,percent);
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
    else {
      Wings.set(false);
    }

    if(Controller1.ButtonX.pressing())
    {
      Climb.set(true);
    }else{
      Climb.set(false);
    }
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

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
