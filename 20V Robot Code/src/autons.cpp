#include "vex.h"
#include <cmath>

void VisionChase(float speed, float pturn, float pdrive, vex::vision::signature vis, float timeout, float lungedist){
  Vision21.takeSnapshot(vis); 
  if(Vision21.objects[0].exists){
    Controller1.Screen.print("A");
    /*if (Vision21.objects[0].height < 40){
      Controller1.Screen.print("B");
      return;
    }
    */
    while (1) {
      Controller1.Screen.print("C");
      bool aligned1=true;
      Vision21.takeSnapshot(vis); 

      double visXerr = v_screen_width/2.0-Vision21.objects[0].centerX;
      int visHerr=Vision21.objects[0].height - 115;
      double turnL = 0;
      double turnR = 0;

      if(visXerr > 50 || visXerr <-50){
        turnR-=visXerr*pturn;
        turnL+=visXerr*pturn;
        aligned1=false;
      }

      if(Vision21.objects[0].height < 100){
        turnR+= visHerr*-pdrive;
        turnL+= visHerr*-pdrive;
        aligned1=false;
      }

      DriveL1.spin(forward,turnL*speed,percent);
      DriveL2.spin(forward,turnL*speed,percent);
      DriveL3.spin(forward,turnL*speed,percent);
      DriveR1.spin(forward,turnR*speed,percent);
      DriveR2.spin(forward,turnR*speed,percent);
      DriveR3.spin(forward,turnR*speed,percent);

      Controller1.Screen.print(aligned1);
      Controller1.Screen.newLine();

      if(aligned1){
        Intake.spin(forward,100, percent);    
        robot.drive_distance(lungedist,robot.get_absolute_heading(),3,3,robot.drive_settle_error,robot.drive_settle_time,500);
        Intake.stop(brake);
      }
    }
  }
}

void default_constants(){
  robot.set_drive_constants(10, 1.5, 0, 10, 0);
  robot.set_heading_constants(6, .4, 0, 1, 0);
  robot.set_turn_constants(12, .4, .03, 3, 15);
  robot.set_swing_constants(12, .3, .001, 2, 15);
  robot.set_drive_exit_conditions(1.5, 300, 5000);
  robot.set_turn_exit_conditions(1, 300, 3000);
  robot.set_swing_exit_conditions(1, 300, 3000);
}

void Skills(){
 
  robot.drive_distance(25);
  robot.turn_to_angle(45);
  robot.drive_distance(-25, robot.get_absolute_heading(), 13, 13,robot.drive_settle_error,robot.drive_settle_time,900);
  PunchMotor.spin(reverse, 100, percent);
  wait(4,seconds);
  PunchMotor.stop();
  robot.drive_distance(40);
  robot.turn_to_angle(0);
  Wings.set(true);
  robot.drive_distance(35);
  robot.turn_to_angle(90);
  Intake.spin(forward,100,percent);
   robot.drive_distance(100, 90, 13, 13,robot.drive_settle_error,robot.drive_settle_time,5000);
  Intake.spin(reverse,100,percent);
  robot.drive_distance(40,90,13,13);
}

void Close_Mid_Score(){

  robot.set_coordinates(0, 0, 0);

  robot.drive_distance(40,20,12,10);
  robot.drive_distance(20,5);
  Intake.spin(forward,100,percent);
  robot.drive_distance(7);
  wait(0.4, sec);
  Intake.stop();
  robot.right_swing_to_angle(90,12,robot.swing_settle_error,robot.swing_settle_time,600,robot.swing_kp,robot.swing_ki,robot.swing_kd,robot.swing_starti);
  robot.drive_distance(32,90,12,robot.heading_max_voltage,robot.drive_settle_error,robot.drive_settle_time,2000);      
  Intake.spin(reverse, 100, percent);
  wait(0.3, seconds);
  Intake.stop();
  robot.drive_distance(-4);
  
  robot.turn_to_angle(0);
  Wings.set(true);
  robot.drive_distance(13,0);
  Wings.set(false);
  robot.drive_distance(-20,20);
  robot.turn_to_angle(210);
  Intake.spin(forward,100,percent);
  robot.drive_distance(44,218);
  Intake.stop();
  robot.turn_to_angle(315);
  
  robot.drive_distance(17);
  Intake.spin(reverse,100,percent);
  robot.drive_distance(9,0);

   robot.drive_distance(4,0,12,12);
   Intake.stop();
     
}

void Close_Desc_Mid(){

  robot.set_coordinates(0, 0, 315);

  robot.drive_distance(8,315);

  Wings.set(true);
  robot.swing_speed_scalar(9, 90, 4, 0.5, false);
  Wings.set(false);

  robot.turn_to_angle(65,12);

  PunchMotor.setVelocity(100, percent);
  PunchMotor.spinFor(forward, -2.938, turns);
  robot.drive_distance(9);
  robot.swing_speed_scalar(40, 0, 12, 1, false);

  Vision21.takeSnapshot(Vision21__GO);
  if(Vision21.objects[0].exists&&Vision21.objects[0].height > 50){
    Intake.spin(forward,100,percent);
    robot.drive_distance(11);
    wait(0.4, sec);
    Intake.stop();
    robot.right_swing_to_angle(90,robot.swing_max_voltage,robot.swing_settle_error,robot.swing_settle_time,600,robot.swing_kp,robot.swing_ki,robot.swing_kd,robot.swing_starti);
    robot.drive_distance(33,90,12,robot.heading_max_voltage,robot.drive_settle_error,robot.drive_settle_time,1300);      
    Intake.spin(reverse, 100, percent);
    wait(0.3, seconds);
    Intake.stop();
    robot.drive_distance(-4);
  } 
}

void Close_Desc_Shoot_Touch(){
  robot.set_coordinates(0, 0, 315);
  robot.drive_distance(8,315);
  Wings.set(true);
  robot.swing_speed_scalar(9, 90, 4, 0.5, false);

  Wings.set(false);

  robot.turn_to_angle(65);

  PunchMotor.setVelocity(100, percent);
  PunchMotor.spinFor(forward, -2.938, turns);
  
  robot.set_drive_constants(12, 1.5, 0, 10, 0);
  
  robot.turn_to_point(0,0);
  robot.drive_to_point(6, -8.5);
  Controller1.Screen.print(robot.odom.X_position);
  Controller1.Screen.print(" ");
  Controller1.Screen.print(robot.odom.Y_position);
  robot.turn_to_angle(90);
  robot.drive_distance(45);  

}

void Close_Score_Desc_Touch(){
  //touch + score + desc (brings to side)
  robot.set_coordinates(0, 0, 0);

  robot.set_drive_constants(12, 4, 0, 20, 0);
  robot.swing_speed_scalar(25, 315, 12, 0.5, true);
  robot.swing_speed_scalar(15, 0, 12, 0.5, false);
 
  Intake.spin(reverse,100,percent);
  wait(0.5,seconds);
  Intake.stop();
  robot.set_coordinates(0, 0, robot.get_absolute_heading());
   robot.drive_distance(2);
  robot.drive_distance(-2);
  robot.swing_speed_scalar(-25, 315, 6.5, 0.35, true);
  wait(0.5,sec);
  Wings.set(true);
   robot.swing_speed_scalar(-15, 270, 12, 0.1, false);
   Wings.set(false);
   robot.drive_distance(7);
   robot.turn_to_angle(135);
   robot.drive_distance(-10);
   robot.drive_distance(3);
  robot.drive_distance(29, 90, 11, 5);
  Wings.set(true);
  
  robot.drive_distance(18);
   //bool didsee = VisionChase();
    
    //robot.turn_to_angle(90);
    //robot.drive_distance(50);
  /*robot.drive_to_point(16, -16);
  Wings.set(true);
  robot.swing_speed_scalar(15, 0, 12, 0.75, false);
  Wings.set(false);
  // robot.turn_to_angle(270);
  robot.drive_distance(-15, 290,7,7);
 
  VisionChase();*/
   /*
  Controller1.Screen.print(robot.get_absolute_heading());

  
  robot.drive_to_point(2, 5);
  //robot.set_drive_constants(12, 1.5, 0, 10, 0);
  */

}

void Far_Score(){
  robot.set_drive_constants(12, 4, 0, 20, 0);
  robot.set_coordinates(0, 0, 270);

  VisionChase(1,0.22,0.55,Vision21__GO,3000,8);

  robot.drive_to_point(0, 0,12,12);
 
  robot.swing_speed_scalar(-45, 180, 12, 0.5, true);
  robot.turn_to_angle(180);
  robot.drive_distance(-13,180,12,12,robot.drive_settle_error,0,700);
 
  robot.turn_to_angle(0);

  Intake.spin(reverse,100,percent);
  wait(0.5,seconds);
 
  robot.drive_distance(4,0,12,12,robot.drive_settle_error,robot.drive_settle_time,300);
  robot.drive_distance(-6);
  Intake.stop();

  robot.turn_to_angle(270);
  
  robot.drive_distance(15,290);
  VisionChase(2, 0.22,0.55, Vision21__GO,4000,8);
  robot.drive_distance(-10);

  Wings.set(true);
  robot.drive_distance(20,80,12,12,robot.drive_settle_error,0,1000);
  Intake.spin(reverse,100,percent);
  robot.drive_distance(30,80,12,12,robot.drive_settle_error,0,2000);
  robot.drive_distance(10);

}

////UNINFINSHED
void Far_Score_Touch(){
  robot.set_drive_constants(12, 4, 0, 20, 0);
  robot.set_coordinates(0, 0, 270);
  VisionChase(1,0.22,0.55,Vision21__GO,4000,8);
  robot.drive_to_point(0, 0);
  
  robot.swing_speed_scalar(-45, 180, 12, 0.5, true);
  robot.turn_to_angle(180);
  robot.drive_distance(-13,180,12,12,robot.drive_settle_error,robot.drive_settle_time,700);
  robot.drive_distance(10);
  robot.turn_to_angle(0);
  robot.drive_distance(5);
  Intake.spin(reverse,100,percent);
  wait(0.5,seconds);
 
  robot.drive_distance(-2);
  robot.drive_distance(6);
  robot.drive_distance(-4);
  Intake.stop();

  //ADD TOUCH

}

void Sit(){} //Do Nothing

void odom_constants(){
  default_constants();
  robot.drive_max_voltage = 8;
  robot.drive_settle_error = 3;
}

void drive_test(){
  robot.drive_distance(6);
  robot.drive_distance(12);
  robot.drive_distance(18);
  robot.drive_distance(-36);
}

void turn_test(){
  robot.turn_to_angle(5);
  robot.turn_to_angle(30);
  robot.turn_to_angle(90);
  robot.turn_to_angle(225);
  robot.turn_to_angle(0);
}

void swing_test(){
  robot.left_swing_to_angle(90);
  robot.right_swing_to_angle(0);
}

void full_test(){
  robot.drive_distance(24);
  robot.turn_to_angle(-45);
  robot.drive_distance(-36);
  robot.right_swing_to_angle(-90);
  robot.drive_distance(24);
  robot.turn_to_angle(0);
}

void odom_test(){
  robot.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", robot.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", robot.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", robot.get_absolute_heading());
    task::sleep(20);
  }
}

void tank_odom_test(){
  odom_constants();
  robot.set_coordinates(0, 0, 0);
  robot.turn_to_point(24, 24);
  robot.drive_to_point(24,24);
  robot.drive_to_point(0,0);
  robot.turn_to_angle(0);
}

void VisTest(){
  VisionChase(2, 0.22,0.55,Vision21__GO,4000,8);
}
