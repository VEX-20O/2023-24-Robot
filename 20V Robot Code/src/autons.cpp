#include "vex.h"
#include <cmath>

bool VisionChase(float sp){
  Vision21.takeSnapshot(Vision21__GO); 
  if(Vision21.objects[0].exists){
    Controller1.Screen.print("A");
    /*if (Vision21.objects[0].height < 40){
      Controller1.Screen.print("B");
      return false;
    }
    */
    while (1) {
      Controller1.Screen.print("C");
      bool aligned1=true;
      Vision21.takeSnapshot(Vision21__GO); 

      float kdp = 0.22;
      double visXerr = v_screen_width/2.0-Vision21.objects[0].centerX;
      int visHerr=Vision21.objects[0].height - 115;
      double turnL = 0;
      double turnR = 0;

      if(visXerr > 50 || visXerr <-50){
        turnR-=visXerr*kdp;
        turnL+=visXerr*kdp;
        aligned1=false;
      }

      if(Vision21.objects[0].height > 130 || Vision21.objects[0].height < 100){
        turnR+= visHerr*-0.55;
        turnL+= visHerr*-0.55;
        aligned1=false;
      }

      DriveL1.spin(forward,turnL*sp,percent);
      DriveL2.spin(forward,turnL*sp,percent);
      DriveL3.spin(forward,turnL*sp,percent);
      DriveR1.spin(forward,turnR*sp,percent);
      DriveR2.spin(forward,turnR*sp,percent);
      DriveR3.spin(forward,turnR*sp,percent);

      Controller1.Screen.print(aligned1);
      Controller1.Screen.newLine();

      if(aligned1){
        Intake.spin(forward,100, percent);    
        chassis.drive_distance(6,chassis.get_absolute_heading(),3,3);
        Intake.stop(brake);
        return true;
      }
    }
  }
  Controller1.Screen.print("D");
    return(false);
}

void Skills(){
  chassis.drive_distance(25);
  chassis.turn_to_angle(45);
  chassis.drive_distance(-25, chassis.get_absolute_heading(), 13, 13,chassis.drive_settle_error,chassis.drive_settle_time,900);
  PunchMotor.spin(reverse, 100, percent);
  wait(2,seconds);
  PunchMotor.stop();
  chassis.drive_distance(40);
  chassis.turn_to_angle(0);
  Wings.set(true);
  chassis.drive_distance(35);
  chassis.turn_to_angle(90);
  Intake.spin(forward,100,percent);
   chassis.drive_distance(100, 90, 13, 13,chassis.drive_settle_error,chassis.drive_settle_time,5000);
  Intake.spin(reverse,100,percent);
  chassis.drive_distance(40,90,13,13);
 

}

bool VisionChase1(float sp){
  Vision21.takeSnapshot(Vision21__GO); 
  if(Vision21.objects[0].exists){
    Controller1.Screen.print("A");
    /*if (Vision21.objects[0].height < 40){
      Controller1.Screen.print("B");
      return false;
    }
    */
    while (1) {
      Controller1.Screen.print("C");
      bool aligned1=true;
      Vision21.takeSnapshot(Vision21__GO); 

      float kdp = 0.22;
      double visXerr = v_screen_width/2.0-Vision21.objects[0].centerX;
      int visHerr=Vision21.objects[0].height - 115;
      double turnL = 0;
      double turnR = 0;

      if(visXerr > 50 || visXerr <-50){
        turnR-=visXerr*kdp;
        turnL+=visXerr*kdp;
        aligned1=false;
      }

      if(Vision21.objects[0].height < 100){
        turnR+= visHerr*-0.55;
        turnL+= visHerr*-0.55;
        aligned1=false;
      }

      DriveL1.spin(forward,turnL*sp,percent);
      DriveL2.spin(forward,turnL*sp,percent);
      DriveL3.spin(forward,turnL*sp,percent);
      DriveR1.spin(forward,turnR*sp,percent);
      DriveR2.spin(forward,turnR*sp,percent);
      DriveR3.spin(forward,turnR*sp,percent);

      Controller1.Screen.print(aligned1);
      Controller1.Screen.newLine();

      if(aligned1){
        Intake.spin(forward,100, percent);    
        chassis.drive_distance(6,chassis.get_absolute_heading(),3,3,chassis.drive_settle_error,chassis.drive_settle_time,500);
        Intake.stop(brake);
        return true;
      }
    }
  }
  Controller1.Screen.print("D");
    return(false);
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

void OppSide_Desc_Mid(){

  chassis.set_coordinates(0, 0, 315);

  chassis.drive_distance(8,315);

 Wings.set(true);
  chassis.swing_speed_scalar(9, 90, 4, 0.5, false);

  Wings.set(false);
  
        

  chassis.turn_to_angle(65,12);

  PunchMotor.setVelocity(100, percent);
  PunchMotor.spinFor(forward, -2.938, turns);
  
  chassis.swing_speed_scalar(45, 20, 12, 1, false);

  Vision21.takeSnapshot(Vision21__GO);
  if(Vision21.objects[0].exists&&Vision21.objects[0].height > 50){
    Intake.spin(forward,100,percent);
      chassis.drive_distance(9);
      wait(0.4, sec);
      Intake.stop();
      chassis.right_swing_to_angle(90,chassis.swing_max_voltage,chassis.swing_settle_error,chassis.swing_settle_time,600,chassis.swing_kp,chassis.swing_ki,chassis.swing_kd,chassis.swing_starti);
      
     
      chassis.drive_distance(33,90,12,chassis.heading_max_voltage,chassis.drive_settle_error,chassis.drive_settle_time,1300);      
       Intake.spin(reverse, 100, percent);
      wait(0.3, seconds);
      Intake.stop();
      chassis.drive_distance(-4);

      }
      
}

void Opp_WP(){
  chassis.set_coordinates(0, 0, 315);
  chassis.drive_distance(8,315);
  Wings.set(true);
  chassis.swing_speed_scalar(9, 90, 4, 0.5, false);

  Wings.set(false);

  chassis.turn_to_angle(65);

  PunchMotor.setVelocity(100, percent);
  PunchMotor.spinFor(forward, -2.938, turns);
  

  chassis.set_drive_constants(12, 1.5, 0, 10, 0);
  
  chassis.turn_to_point(0,0);
  chassis.drive_to_point(6, -8.5);
    Controller1.Screen.print(chassis.odom.X_position);
      Controller1.Screen.print(" ");
   Controller1.Screen.print(chassis.odom.Y_position);
   chassis.turn_to_angle(90);
  chassis.drive_distance(45);  


}

void OppSide_Desc_Score_Score(){
  chassis.set_coordinates(0, 0, 0);

  
  chassis.set_drive_constants(12, 4, 0, 20, 0);
  chassis.swing_speed_scalar(25, 315, 12, 0.5, true);
  chassis.swing_speed_scalar(15, 0, 12, 0.5, false);
 
  Intake.spin(reverse,100,percent);
  wait(0.5,seconds);
  Intake.stop();
  chassis.set_coordinates(0, 0, chassis.get_absolute_heading());
   chassis.drive_distance(2);
  chassis.drive_distance(-2);
  chassis.swing_speed_scalar(-25, 315, 6.5, 0.35, true);
  wait(0.5,sec);
  Wings.set(true);
   chassis.swing_speed_scalar(-15, 270, 12, 0.1, false);
   Wings.set(false);
   chassis.drive_distance(7);
   chassis.turn_to_angle(135);
   chassis.drive_distance(-10);
  chassis.drive_distance(27, 90, 11, 5);
  
  chassis.drive_distance(37);
   //bool didsee = VisionChase();
    
    //chassis.turn_to_angle(90);
    //chassis.drive_distance(50);
  /*chassis.drive_to_point(16, -16);
  Wings.set(true);
  chassis.swing_speed_scalar(15, 0, 12, 0.75, false);
  Wings.set(false);
  // chassis.turn_to_angle(270);
  chassis.drive_distance(-15, 290,7,7);
 
  VisionChase();*/
   /*
  Controller1.Screen.print(chassis.get_absolute_heading());

  
  chassis.drive_to_point(2, 5);
  //chassis.set_drive_constants(12, 1.5, 0, 10, 0);
  */

}

void SameSide_Score(){
  chassis.set_drive_constants(12, 4, 0, 20, 0);
  chassis.set_coordinates(0, 0, 270);
  bool a = VisionChase(3);
  chassis.drive_to_point(0, 0,12,12);
  //chassis.drive_distance(-15, 270);
  chassis.swing_speed_scalar(-45, 180, 12, 0.5, true);
  chassis.turn_to_angle(180);
  chassis.drive_distance(-13,180,12,12,chassis.drive_settle_error,0,700);
  //chassis.drive_distance(10);
  chassis.turn_to_angle(0);
  //chassis.drive_distance(5);
  Intake.spin(reverse,100,percent);
  wait(0.5,seconds);
 
 
  chassis.drive_distance(4,0,12,12,chassis.drive_settle_error,chassis.drive_settle_time,300);
  chassis.drive_distance(-6);
   Intake.stop();

  chassis.turn_to_angle(270);
  
  chassis.drive_distance(15,290);
  VisionChase1(2);
  chassis.drive_distance(-10);
  Wings.set(true);
  chassis.drive_distance(42,80,12,12,chassis.drive_settle_error,0,4000);
  Intake.spin(reverse,100,percent);

}

void SameSide_NoMid(){
  chassis.set_drive_constants(12, 4, 0, 20, 0);
  chassis.set_coordinates(0, 0, 270);
  bool a = VisionChase(1);
  chassis.drive_to_point(0, 0);
  //chassis.drive_distance(-15, 270);
  chassis.swing_speed_scalar(-45, 180, 12, 0.5, true);
  chassis.turn_to_angle(180);
  chassis.drive_distance(-13,180,12,12,chassis.drive_settle_error,chassis.drive_settle_time,700);
  chassis.drive_distance(10);
  chassis.turn_to_angle(0);
  chassis.drive_distance(5);
  Intake.spin(reverse,100,percent);
  wait(0.5,seconds);
 
  chassis.drive_distance(-2);
  chassis.drive_distance(6);
  chassis.drive_distance(-4);
   Intake.stop();
}

void Sit(){}

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

void VisTest(){
  bool a = VisionChase1(2);
}
