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

int autonomousSelection = 0;
bool autonenabeld = true;
bool ledtoggle = true;
bool side = false;

typedef struct _button {
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    bool   state;
    vex::color offColor;
    vex::color onColor;
    const char *label;
} button;

// Button array definitions for each software button. The purpose of each button data structure
// is defined above.  The array size can be extended, so you can have as many buttons as you 
// wish as long as it fits.
button buttons[] = {
    {   30,  30, 60, 60,  false, 0x404040, 0x404040, "Auton Next" },
    {  150,  30, 60, 60,  false, 0x303030, 0xD0D0D0, "Auton Off" },
 //   {  270,  30, 60, 60,  false, 0x303030, 0xF700FF, "Park" },
  //  {  390,  30, 60, 60,  false, 0x303030, 0xDDDD00, "Shoot" },
    {   30, 150, 60, 60,  false, 0xE00000, 0x0000E0, "Switch Side" },
    {  150, 150, 60, 60,  true, 0x404040, 0xC0C0C0, "LED Toggle" },
 //   {  270, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "6-" },
 //   {  390, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "7-" }
};

// forward ref
void displayButtonControls( int index, bool pressed );

/*-----------------------------------------------------------------------------*/
/** @brief      Check if touch is inside button                                */
/*-----------------------------------------------------------------------------*/
int
findButton(  int16_t xpos, int16_t ypos ) {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &buttons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}

/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/
void
initButtons() {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      buttons[index].state = false;
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been touched                                        */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackPressed() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton( xpos, ypos )) >= 0 ) {
      displayButtonControls( index, true );
    }

}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackReleased() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton( xpos, ypos )) >= 0 ) {
      // clear all buttons to false, ie. unselected
      //      initButtons(); 

      // now set this one as true
      if( buttons[index].state == true) {
        buttons[index].state = false; 
      }
      else    {
        buttons[index].state = true;
      }


      // save as auton selection
      if(index == 0){
        autonomousSelection++;
        if(autonomousSelection == 8){
          autonomousSelection=0;
        }
        
        switch(autonomousSelection){       //Tap the brain screen to cycle through autons.
      if(index==1){
        autonomousSelection=7;
      }
      case 0:
        Controller1.Screen.print(AUTO1);
        Brain.Screen.printAt(300, 100, AUTO1);
       // DrawAuto1();
        break;
      case 1:
        Controller1.Screen.print(AUTO2);
        Brain.Screen.printAt(300, 100, AUTO2);
       // DrawAuto2();
        break;
      case 2:
        Controller1.Screen.print(AUTO3);
        Brain.Screen.printAt(300, 100, AUTO3);
        //DrawAuto3();
        break;
      case 3:
        Controller1.Screen.print(AUTO4);
        Brain.Screen.printAt(300, 100, AUTO4);
         // DrawAuto4();
        break;
      case 4:
        Controller1.Screen.print(AUTO5);
        Brain.Screen.printAt(300, 100, AUTO5);
        //DrawAuto5();
        break;
      case 5:
        Controller1.Screen.print(AUTO6);
        Brain.Screen.printAt(300, 100, AUTO6);
        //DrawAuto6();
        break;
      case 6:
        Controller1.Screen.print(AUTO7);
        Brain.Screen.printAt(300, 100, AUTO7);
        //DrawAuto7();
        break;
      case 7:
        Controller1.Screen.print(AUTO8);
        Brain.Screen.printAt(300, 100, AUTO8);
        break;
    }

      }

      
      

      displayButtonControls( index, false );
    }

}

/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/
void
displayButtonControls( int index, bool pressed ) {
    vex::color c;
    Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

    for(int i=0;i<sizeof(buttons)/sizeof(button);i++) {

      if( buttons[i].state )
        c = buttons[i].onColor;
      else
        c = buttons[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c );
      }
      else
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );

      // outline
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, vex::color::transparent );

// draw label
      if(  buttons[i].label != NULL )   
        Brain.Screen.setFillColor(black);                                          //was 8
        Brain.Screen.printAt( buttons[i].xpos + 8, buttons[i].ypos + buttons[i].height + 8, buttons[i].label );
    }
}

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

bool auto_started = false;
bool isIntake = false;

void ToggleBlock();

void pre_auton(void) {

  sylib::initialize();

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();

  auto BackLights = sylib::Addrled(22, 1, 42);
  auto BottomBack = sylib::Addrled(22, 2, 42);
  auto FrontLights = sylib::Addrled(22, 3, 42);
  auto BottomFront = sylib::Addrled(22, 4, 42);
  BackLights.clear();
  BottomBack.clear();
  FrontLights.clear();
  BottomFront.clear();
  BackLights.set_all(LEDRED);
  BottomBack.set_all(LEDRED);
  FrontLights.set_all(LEDRED);
  BottomFront.set_all(LEDRED);

/*
  while(auto_started==false){
    
    side = buttons[2].state;
    ledtoggle = buttons[3].state;

    if(!ledtoggle){
      BottomFront.turn_off();
      FrontLights.turn_off();
      BottomFront.turn_off();
      BottomBack.turn_off();
    }
    else{
      BottomFront.turn_on();
      FrontLights.turn_on();
      BottomFront.turn_on();
      BottomBack.turn_on();
    }
    if(side==false){
      BackLights.set_all(LEDRED);
      BottomBack.set_all(LEDRED);
      FrontLights.set_all(LEDRED);
      BottomFront.set_all(LEDRED);
    }
    else{
      BackLights.set_all(LEDBLUE);
      BottomBack.set_all(LEDBLUE);
      FrontLights.set_all(LEDBLUE);
      BottomFront.set_all(LEDBLUE);
    }
    this_thread::sleep_for(10);
  }

  this_thread::sleep_for(10);

/*
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

    task::sleep(100);
  }
*/
}


void autonomous(void) {
  auto_started = true;
  switch(autonomousSelection){  
    case 0:
      Skills();
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
  if(side==false && ledtoggle){
      BackLights.set_all(LEDRED);
      BottomBack.set_all(LEDRED);
      FrontLights.set_all(LEDRED);
      BottomFront.set_all(LEDRED);
    }
    else if (ledtoggle){
      BackLights.set_all(LEDBLUE2);
      BottomBack.set_all(LEDBLUE2);
      FrontLights.set_all(LEDBLUE2);
      BottomFront.set_all(LEDBLUE2);
    }
  if(!ledtoggle){
    BackLights.clear();
    BottomBack.clear();
    FrontLights.clear();
    BottomFront.clear();
    BottomFront.turn_off();
    FrontLights.turn_off();
    BottomFront.turn_off();
    BottomBack.turn_off();
  }
  
  // User control code here, inside the loop
  while (1) {

    if(IDistance.objectDistance(mm) < INTAKEDISTANCECONST && !isIntake){
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
     if (ledtoggle){
      BackLights.set_all(LEDGREEN);
      BottomBack.set_all(LEDGREEN);
      FrontLights.set_all(LEDGREEN);
      BottomFront.set_all(LEDGREEN);
     }
    }
    else if (IDistance.objectDistance(mm) > INTAKEDISTANCECONST && isIntake){
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
      if(side==false && ledtoggle){
      BackLights.set_all(LEDRED);
      BottomBack.set_all(LEDRED);
      FrontLights.set_all(LEDRED);
      BottomFront.set_all(LEDRED);
    }
    else if (ledtoggle){
      BackLights.set_all(LEDBLUE2);
      BottomBack.set_all(LEDBLUE2);
      FrontLights.set_all(LEDBLUE2);
      BottomFront.set_all(LEDBLUE2);
    }
    }

    //Drive function call
    //Replace this line with robot.control_tank(); for tank drive 
    robot.control_arcade(ARCADETURNINGCONST);
    
    //Punch Catapult Code
    if(Controller1.ButtonR1.pressing()){
      PunchMotor.spin(reverse, PUNCHERVOLTAGECONST, volt); //was 10.5
    }
    else{
      PunchMotor.stop();
    }

    //Intake Code
    if(Controller1.ButtonR2.pressing()){
      Intake.spin(forward,INTAKESPEEDFWDCONST,percent);
      if(IDistance.objectDistance(mm) < INTAKEDISTANCECONST){
        Intake.spin(forward, INTAKESPEEDIDLECONST, percent);
      }
    }
    else if(Controller1.ButtonL2.pressing()){
      Intake.spin(reverse,INTAKESPEEDREVCONST,percent);
    }
    else if (!isIntake){
      Intake.stop();
    }
    
    //Pneumatic Wings
    if(Controller1.ButtonL1.pressing())
    {
      Wings.set(true);
      Intake.spin(reverse,INTAKESPEEDREVCONST,percent);
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

    //Run the pre-autonomous function. 
    pre_auton();

    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    // register events for button selection
    Brain.Screen.pressed( userTouchCallbackPressed );
    Brain.Screen.released( userTouchCallbackReleased );

    // make nice background
    Brain.Screen.setFillColor( vex::color(0x404040) );
    Brain.Screen.setPenColor( vex::color(0x404040) );
    Brain.Screen.drawRectangle( 0, 0, 480, 240 );

    auto BackLights = sylib::Addrled(22, 1, 42);
    
    auto BottomBack = sylib::Addrled(22, 2, 42);
    auto FrontLights = sylib::Addrled(22, 3, 42);
    auto BottomFront = sylib::Addrled(22, 4, 42);
    BackLights.clear();
    BottomBack.clear();
    FrontLights.clear();
    BottomFront.clear();
    BackLights.set_all(LEDRED);
    BottomBack.set_all(LEDRED);
    FrontLights.set_all(LEDRED);
    BottomFront.set_all(LEDRED);

    Controller1.Screen.print(AUTO1);
        Brain.Screen.printAt(300, 100, AUTO1);

    // initial display
    displayButtonControls( 0, false );

    while(1) {
        // Allow other tasks to run
        if( !Competition.isEnabled() && !auto_started  ){
        
        Brain.Screen.setFont(fontType::mono20);
        Brain.Screen.setFillColor( vex::color(0xFFFFFF) );

        Brain.Screen.setPenColor( vex::color(0xc11f27));
        Brain.Screen.printAt( 0,  135, "  Regents Robotics 20V  " );


        side = buttons[2].state;
        ledtoggle = buttons[3].state;

        if(!ledtoggle){
          BackLights.clear();
          BottomBack.clear();
          FrontLights.clear();
          BottomFront.clear();
          BottomFront.turn_off();
          FrontLights.turn_off();
          BottomFront.turn_off();
          BottomBack.turn_off();
        }
        else{
          BottomFront.turn_on();
          FrontLights.turn_on();
          BottomFront.turn_on();
          BottomBack.turn_on();
        }

    if(side==false && ledtoggle){
      BackLights.set_all(LEDRED);
      BottomBack.set_all(LEDRED);
      FrontLights.set_all(LEDRED);
      BottomFront.set_all(LEDRED);
    }
    else if (ledtoggle){
      BackLights.set_all(LEDBLUE2);
      BottomBack.set_all(LEDBLUE2);
      FrontLights.set_all(LEDBLUE2);
      BottomFront.set_all(LEDBLUE2);
    }

    autonenabeld = buttons[1].state;

        this_thread::sleep_for(10);
    }
    }
}

void ToggleBlock(){
  Blocker.set(!Blocker.value());
}
