#include "vex.h"
#include <cmath>

void default_constants(){
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void hunt_auto(){

chassis.set_coordinates(0,0,0);

default_constants();

//chassis.drive_distance(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti)

Intake.spin(forward,9,volt);
chassis.drive_distance(30, 0, 11, 11);
Intake.stop();
chassis.drive_distance(-15, 0, 9, 9);
chassis.turn_to_angle(45);
chassis.drive_distance(-10,0,9,9);
Wings.set(true);
chassis.drive_distance(-10, 90, 9, 9);
chassis.turn_to_point(0, 0);

//chassis.drive_to_point(0, 0);


/*chassis.turn_to_angle(0);

chassis.drive_distance(30);
chassis.turn_to_angle(90);

//from here

Vision21.takeSnapshot(Vision21__GO); 
  double vis = 320-Vision21.objects[0].centerX;
  while(vis > 25 || vis <-25){
    
    chassis.turn_to_angle(chassis.get_absolute_heading()+abs(vis)/vis*15);
    Vision21.takeSnapshot(Vision21__GO); 
    vis = 320/2-Vision21.objects[0].centerX;
  }

  while(Vision21.objects[0].width < 200){
      chassis.drive_distance(4);
       Vision21.takeSnapshot(Vision21__GO);
    }

  Intake.spin(forward,  100,percent);
  chassis.drive_distance(5);
  
  Intake.stop();
  chassis.turn_to_angle(180);
  chassis.drive_to_point(float X_position, float Y_position);
  Intake.spin(reverse, 10, volt);
  wait(2, seconds);
  Intake.stop();

  //to here
*/



/*
int turncons = 15;

default_constants();
 chassis.drive_max_voltage = 5;

Vision21.takeSnapshot(Vision21__GO); 
  double vis = 320-Vision21.objects[0].centerX;
  while(vis > 25 || vis <-25){
    
    chassis.turn_to_angle(chassis.get_absolute_heading()+abs(vis)/vis*15);
    Vision21.takeSnapshot(Vision21__GO); 
    vis = 320/2-Vision21.objects[0].centerX;
    Controller1.Screen.print(vis);
    Controller1.Screen.newLine(); 
  }

  while(Vision21.objects[0].width < 200){
    
      chassis.drive_distance(4);
       Vision21.takeSnapshot(Vision21__GO);
    }
  Intake.spin(forward,  100,percent);
  chassis.drive_distance(5);
  

//chassis.turn_to_angle(10);
//chassis.drive_distance(15);


*/
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}