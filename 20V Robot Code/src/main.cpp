// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// DriveL1              motor         1               
// DriveL2              motor         2               
// DriveL3              motor         3               
// DriveR1              motor         9               
// DriveR2              motor         8               
// DriveR3              motor         10              
// Inertial11           inertial      11              
// Controller1          controller                    
// Wings                digital_out   H               
// PunchMotor           motor         5               
// Vision21             vision        21              
// Intake               motor         4               
// Blocker              digital_out   G               
// Climb                digital_out   E               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <string>
#include "sylib/sylib.hpp"

using namespace vex;
competition Competition;

Drive robot(

ZERO_TRACKER_ODOM, 

//Left Motors:
motor_group(DriveL1,DriveL2,DriveL3),
//Right Motors:
motor_group(DriveR1,DriveR2,DriveR3),

//PORT NUMBER of inertial
PORT11,

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
bool isIntake = false;

#define LEDRED 0xFE0202
#define LEDBLUE 0x02AAFE
#define LEDMAGENTA 0xE62169
#define LEDGREEN 0x56FE02

float INTAKEVAL = 200.0;

void ToggleBlock();

void pre_auton(void) {

  sylib::initialize();

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();
/*
  auto BackLights = sylib::Addrled(22, 1, 42);
  auto BottomBack = sylib::Addrled(22, 2, 42);
  auto FrontLights = sylib::Addrled(22, 3, 42);
  auto BottomFront = sylib::Addrled(22, 4, 42);
  auto colors = std::vector<std::uint32_t>();
  colors.resize(42);
  for(int i = 0; i < colors.size(); i++){
    colors[i] = sylib::Addrled::rgb_to_hex(i*30 , 1, 0.25);
  }

  BackLights.set_buffer(colors);
  BottomBack.set_buffer(colors);
  FrontLights.set_buffer(colors);
  BottomFront.set_buffer(colors);
*/
  while(auto_started == false){            //Changing the names below will only change their names on the
    Brain.Screen.clearScreen();            //brain screen for auton selection.
    Controller1.Screen.clearLine();
    switch(current_auton_selection){       //Tap the brain screen to cycle through autons.
      case 0:
        Controller1.Screen.print(AUTO1);
        Brain.Screen.printAt(50, 50, AUTO1);
        DrawAuto1();
        break;
      case 1:
        Controller1.Screen.print(AUTO2);
        Brain.Screen.printAt(50, 50, AUTO2);
        DrawAuto2();
        break;
      case 2:
        Controller1.Screen.print(AUTO3);
        Brain.Screen.printAt(50, 50, AUTO3);
        DrawAuto3();
        break;
      case 3:
        Controller1.Screen.print(AUTO4);
        Brain.Screen.printAt(50, 50, AUTO4);
          DrawAuto4();
        break;
      case 4:
        Controller1.Screen.print(AUTO5);
        Brain.Screen.printAt(50, 50, AUTO5);
        DrawAuto5();
        break;
      case 5:
        Controller1.Screen.print(AUTO6);
        Brain.Screen.printAt(50, 50, AUTO6);
        DrawAuto6();
        break;
      case 6:
        Controller1.Screen.print(AUTO7);
        Brain.Screen.printAt(50, 50, AUTO7);
        DrawAuto7();
        break;
      case 7:
        Controller1.Screen.print(AUTO8);
        Brain.Screen.printAt(50, 50, AUTO8);
        break;
    }

    if (Brain.Screen.pressing() || Controller1.ButtonA.pressing()){
      while(Brain.Screen.pressing() || Controller1.ButtonA.pressing()) {}
      current_auton_selection ++;
    } 
    else if (current_auton_selection == 8){
      current_auton_selection = 0;
    }
/*
    BackLights.rotate(1, false);
    BottomBack.rotate(1, false);
    FrontLights.rotate(1, false);
    BottomFront.rotate(1, false);
*/
    task::sleep(100);
  }
/*
    BackLights.clear();
    BottomBack.clear();
    FrontLights.clear();
    BottomFront.clear();
*/
}

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){  
    case 0:
      Skills();
      //Far_Score_4();
      //Far_Score_Touch();
      //Close_Mid_Score();
      //Close_Score_Desc_Touch();
      break;     
    case 1:        
      Close_Desc_Mid();
      break;
    case 2:
      Close_Mid_Score();
      break;
    case 3:
      Close_Desc_Shoot_Touch();
      break;
    case 4:
      Close_Score_Desc_Touch();
      break;
    case 5:
      Far_Score_5();
      break;
    case 6:
      Far_Score_Touch();
      break;
    case 7:
      Far_Score_4();
      break;
  }
}

void usercontrol(void) {
  
  auto BackLights = sylib::Addrled(22, 1, 42);
  auto BottomBack = sylib::Addrled(22, 2, 42);
  auto FrontLights = sylib::Addrled(22, 3, 42);
  auto BottomFront = sylib::Addrled(22, 4, 42);

  auto_started == true;

  Controller1.ButtonB.pressed(ToggleBlock);

  robot.set_coordinates(0,0,0);

  BackLights.clear();
  BottomBack.clear();
  FrontLights.clear();
  BottomFront.clear();
  BackLights.set_all(LEDRED);
  BottomBack.set_all(LEDRED);
  FrontLights.set_all(LEDRED);
  BottomFront.set_all(LEDRED);
  

  // User control code here, inside the loop
  while (1) {

    if(IDistance.objectDistance(mm) < INTAKEVAL && !isIntake){
      isIntake = true;
      BackLights.clear();
      BottomBack.clear();
      FrontLights.clear();
      BottomFront.clear();
      /*
      BackLights.set_all(0xE62169);
      BottomBack.set_all(0xE62169);
      FrontLights.set_all(0xE62169);
      BottomFront.set_all(0xE62169);
      */
      BackLights.set_all(LEDGREEN);
      BottomBack.set_all(LEDGREEN);
      FrontLights.set_all(LEDGREEN);
      BottomFront.set_all(LEDGREEN);
    }
    else if (IDistance.objectDistance(mm) > INTAKEVAL && isIntake){
      isIntake = false;
      /*
      BackLights.set_all(sylib::Addrled::rgb_to_hex(0 , 255, 255));
      BottomBack.set_all(sylib::Addrled::rgb_to_hex(0 , 255, 255));
      FrontLights.set_all(sylib::Addrled::rgb_to_hex(0 , 255, 255));
      BottomFront.set_all(sylib::Addrled::rgb_to_hex(0, 255, 255));
      */
      BackLights.clear();
      BottomBack.clear();
      FrontLights.clear();
      BottomFront.clear();
      BackLights.set_all(LEDRED);
      BottomBack.set_all(LEDRED);
      FrontLights.set_all(LEDRED);
      BottomFront.set_all(LEDRED);
    }

    //Drive function call
    //Replace this line with robot.control_tank(); for tank drive 
    robot.control_arcade(0.6);
    
    //Punch Catapult Code
    if(Controller1.ButtonR1.pressing()){
      PunchMotor.spin(reverse, 9.5, volt); //was 10.5
    }
    else{
      PunchMotor.stop();
    }

    //Intake Code
    if(Controller1.ButtonR2.pressing()){
      Intake.spin(forward,100,percent);
      if(IDistance.objectDistance(mm) < INTAKEVAL){
        Intake.spin(forward);
      }
    }
    else if(Controller1.ButtonL2.pressing()){
      Intake.spin(reverse,100,percent);
    }
    else if (!isIntake){
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

    //Pneumatic Climb
    if (Controller1.ButtonDown.pressing()){
      Climb.set(true);
    }
    else {
      Climb.set(false);
    }
    
    Controller1.Screen.print(robot.get_X_position());
    Controller1.Screen.print(" ");
    Controller1.Screen.print(robot.get_Y_position());
    Controller1.Screen.newLine();

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

void ToggleBlock(){
  Blocker.set(!Blocker.value());
}
