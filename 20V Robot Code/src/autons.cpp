#include "vex.h"
#include <cmath>

void VisionChase(){
  Vision21.takeSnapshot(Vision21__GO); 
  if(Vision21.objects[0].exists){
  while (1) {
Vision21.takeSnapshot(Vision21__GO); 

    bool aligned1=true;
    
  if(Controller1.ButtonY.pressing()){
    break;
  }

  float kdp = 0.22;
  
  double visE = 316/2-Vision21.objects[0].centerX;
  double turnL = 0;
  double turnR = 0;

  if(visE > 50 || visE <-50){
    turnR-=visE*kdp;
    turnL+=visE*kdp;
    aligned1=false;
  }
  int vish=Vision21.objects[0].height - 115;
  if(Vision21.objects[0].height > 130 || Vision21.objects[0].height < 100){
    turnR+= vish*-0.55;
    turnL+= vish*-0.55;
    aligned1=false;
  }

  DriveL1.spin(forward,turnL,percent);
  DriveL2.spin(forward,turnL,percent);
  DriveL3.spin(forward,turnL,percent);
  DriveR1.spin(forward,turnR,percent);
  DriveR2.spin(forward,turnR,percent);
  DriveR3.spin(forward,turnR,percent);

  Controller1.Screen.print(aligned1);
  Controller1.Screen.newLine();

  if(aligned1){
    Intake.spin(forward,100, percent);    
    chassis.drive_distance(15,chassis.get_absolute_heading(),6,6);
    Intake.stop(brake);
    return;
  }
  }
  }
}

void default_constants(){
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void OppSide_Desc(){
 chassis.set_coordinates(0, 0, 315);
  Wings.set(true);
chassis.drive_dis_half_speed(9, 90, 11, 0.4, false);
 // chassis.set_coordinates(0, 0, 305);
 
  //chassis.left_swing_to_angle(0, 11);
  Wings.set(false);
   
   chassis.turn_to_angle(65);
  PunchMotor.setVelocity(100, percent);
  PunchMotor.spinFor(forward, -2.938, turns);

//add dump over

  chassis.drive_distance(15, 60, 6, 6);
  //chassis.turn_to_point(0, 0);
  chassis.drive_to_point(0, -2);
  chassis.turn_to_angle(135);
  chassis.drive_distance(15);
  chassis.turn_to_angle(90);
  chassis.drive_distance(10);
}

void SameSide_Score(){
  chassis.set_coordinates(0, 0, 270);
  //VisionChase();
  chassis.drive_distance(-10);
  chassis.drive_distance(5);
  chassis.turn_to_angle(90);
  chassis.drive_distance(15);
  Wings.set(true);
  chassis.drive_dis_half_speed(9, 0, 11, 0.4, true);
  Intake.spin(reverse,60,percent);
  chassis.drive_distance(15);
  Wings.set(false);
   Intake.stop();

  //add in 180 degree push if needed

  chassis.turn_to_angle(270);
  chassis.drive_distance(10);
  VisionChase();
  
  chassis.drive_distance(-5);
  chassis.turn_to_angle(90);
  chassis.drive_distance(15);
  Intake.spin(reverse,100, percent);

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
