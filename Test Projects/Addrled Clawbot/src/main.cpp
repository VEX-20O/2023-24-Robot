/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 10, D        
// ClawMotor            motor         3               
// ArmMotor             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "addrled.h"

using namespace vex;

// A global instance of competition
competition Competition;


addressable_led addrled(Brain.ThreeWirePort.A, 64 );
// local storage for some pixel data
uint32_t data[addressable_led::MAX_LEDS];


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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
  // User control code here, inside the loop
  // set all led black
    // probably need some initial delay, TBD
    this_thread::sleep_for(200);    
    addrled.clear();
    this_thread::sleep_for(1000);    

    while(1) {        
        addrled.clear( color(64,0,0) );
        this_thread::sleep_for(1000);    
        addrled.clear( color(0,64,0) );
        this_thread::sleep_for(1000);    
        addrled.clear( color(0,0,64) );
        this_thread::sleep_for(1000);    
        addrled.clear();
        this_thread::sleep_for(50);

        // set one led at a time
        for( int i=0;i<addrled.max();i++ ) {
          uint32_t c = color(64,0,0);
          addrled.set( &c, i, 1, 0 );
          this_thread::sleep_for(50);
        }

        //rainbow
        memset(data, 0, sizeof(data));
        for( int i=0;i<addrled.max();i+=12 ) {
          vex::color c;
          // use low value to keep current down
          for(int j=0;j<12;j++)
            data[i+j] = c.hsv(  j*30, 1, 0.25);    // vex color will be converted to uint32_t
        }

        addrled.set( data, 0, addrled.max(), 0 );
        this_thread::sleep_for(1000);    

        for( int i=0;i<addrled.max()-1;i++ ) {
          addrled.rotate(1);
          addrled.flush();
          this_thread::sleep_for(50);
        }
    }

    // turn all off
    addrled.clear();

    while(1) {
        // Allow other tasks to run
        this_thread::sleep_for(10);
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
