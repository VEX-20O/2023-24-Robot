#include "vex.h"
#include <cmath>

//Leave this, if needed change the constants with a function call in the respective auton
void default_constants(){
  robot.set_drive_constants(10, 1.5, 0, 10, 0);
  robot.set_heading_constants(6, .4, 0, 1, 0);
  robot.set_turn_constants(12, .4, .03, 3, 15);
  robot.set_swing_constants(12, .3, .001, 2, 15);
  robot.set_drive_exit_conditions(1.5, 300, 5000);
  robot.set_turn_exit_conditions(1, 300, 3000);
  robot.set_swing_exit_conditions(1, 300, 3000);
}

//Programming skills
void Skills(){

  //Movement to angle against matchload -> start shooting
  robot.drive_distance(15,0);
  robot.turn_to_angle(65,7);
  robot.drive_distance(-15, robot.get_absolute_heading(), 13, 13, robot.drive_settle_error, robot.drive_settle_time, 900);
  PunchMotor.spin(reverse, 9.5, volt);
  
  //delay for shooting time, then stop puncher to draw less current
  wait(42,seconds);   //was 42  
  PunchMotor.stop();
  
  //Cross barrier and score, then reverse
  robot.drive_distance(40,40);
  robot.turn_to_angle(0);
  Wings.set(true);
  robot.drive_distance(30);
  robot.turn_to_angle(90);
  Intake.spin(forward,100,percent);
  robot.drive_distance(100, 90, 13, 13,robot.drive_settle_error,robot.drive_settle_time,5000);
  Intake.spin(reverse,100,percent);
  robot.drive_distance(40,90,13,13,robot.drive_settle_error,robot.drive_settle_time,3000);
  robot.drive_distance(-30);
  Wings.set(false);
  robot.turn_to_angle(270,12);
  robot.drive_distance(20,270,12,12);
  robot.turn_to_angle(90,12);
  Wings.set(true);
  robot.drive_distance(35,90,12,12);
  robot.drive_distance(-30);

}

//Mid rush to move one triball in mid over the barrier and knock the other, then score preload laying on ground
void Close_Mid_Score(){

  robot.set_coordinates(0, 0, 0); //odom things

  //go to mid-mid triball and grab it
  robot.drive_distance(40,20,12,10);
  robot.drive_distance(20,5);
  Intake.spin(forward,100,percent);
  robot.drive_distance(7);
  wait(0.4, sec);
  Intake.stop();

  //Climb barrier and outtake preload, then face normal
  robot.right_swing_to_angle(90,12,robot.swing_settle_error,robot.swing_settle_time,600,robot.swing_kp,robot.swing_ki,robot.swing_kd,robot.swing_starti);
  robot.drive_distance(32,90,12,robot.heading_max_voltage,robot.drive_settle_error,robot.drive_settle_time,2000);      
  Intake.spin(reverse, 100, percent);
  wait(0.3, seconds);
  Intake.stop();
  robot.drive_distance(-4);
  robot.turn_to_angle(0);

  //Knock second mid triball away from enemy auton path
  Wings.set(true);
  robot.drive_distance(13,0);
  Wings.set(false);

  //Go Score preload
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

//not currently useful. starts by descoring, then launches one over barrier, then goes and throws one over the barrier mid. 
void Close_Desc_Mid(){

  robot.set_coordinates(0, 0, 315); //odom things

  //descore motion (starts 45 deg)
  robot.drive_distance(8,315);
  Wings.set(true);
  robot.swing_speed_scalar(9, 90, 4, 0.5, false);
  Wings.set(false);

  //Launch triball
  robot.turn_to_angle(65,12);
  PunchMotor.setVelocity(100, percent);
  PunchMotor.spinFor(forward, -2.938, turns);
  
  //go for triball mid with vision and climb barrier -> outtake
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

//auton for mid ball rush. UNFINISHED
void Far_Score_MidS(){
  robot.set_coordinates(0, 0, 0); //odom things
}

//score 4-5 triballs in goal. No descore. !MAY GO OVER AUTON LINE, FINISH DEBUGGING!
void Far_Score_5(){

  //Odom and setup things (this auton goes faster than all others / p is lower)
  robot.set_drive_constants(12, 4, 0, 20, 0);
  robot.set_coordinates(0, 0, 270);
  robot.set_drive_exit_conditions(1.5, 0, 1000);

  //get under-bar triball and return to origin
  Intake.spin(forward,100,percent);
  robot.drive_distance(21,270,7,7);//was 23
  wait(0.3,seconds);
  robot.drive_to_point(0, 0,12,12);
  //Intake.stop();

  //score preload
  robot.swing_speed_scalar(-44, 180, 12, 0.5, true);
  robot.turn_to_angle(180,12);
  robot.drive_distance(-13,180,12,12,robot.drive_settle_error,0,700);

  //score ball in intake
  robot.drive_distance(7,180,12,12);
  robot.turn_to_angle(0,12);
  Intake.spin(reverse,100,percent);
  wait(0.3,seconds);
 
  //give them a little tap
  Intake.stop();
  robot.drive_distance(7,0,12,12,robot.drive_settle_error,robot.drive_settle_time,300);
  robot.drive_distance(-6,0,12,12);
 

  //go for first mid triball
  robot.turn_to_angle(270,12);
  Intake.spin(forward,100,percent);
  robot.drive_distance(52,290);

  //spit the triball twoards goal
  robot.drive_distance(-12);
  robot.turn_to_angle(58,12);//was 63
  Intake.spin(reverse,100,percent); //was 63
  wait(0.3,seconds);
  Intake.stop();

  //go for second mid triball
  Intake.spin(forward,100,percent);
  robot.drive_distance(29,350,7,7); //was 30,355

  //robot.set_turn_constants(12, .8, 0, 10, 15);
  //robot.set_turn_constants(12, 2, 0, 10, robot.turn_starti);
  //robot.set_turn_exit_conditions(4, 100, 1300);

  //shoot second to goal
  robot.turn_to_angle(90,12);
  Intake.spin(reverse,100,percent);
  wait(0.25,seconds);
  Intake.stop();

  //go and score last triball
  robot.turn_to_angle(270,12);
  Intake.spin(forward,100,percent);
  robot.drive_distance(15,270,12,12);
  robot.turn_to_angle(90,12);
  Intake.spin(reverse,100,percent);
  Wings.set(true);
  robot.drive_distance(26,90,12,12);
  robot.drive_distance(-6,0,12,12);

}

void Far_Score_4(){

  //Odom and setup things (this auton goes faster than all others / p is lower)
  robot.set_drive_constants(12, 4, 0, 20, 0);
  robot.set_coordinates(0, 0, 270);
  robot.set_drive_exit_conditions(1.5, 0, 1000);

  //get under-bar triball and return to origin
  Intake.spin(forward,100,percent);
  robot.drive_distance(19,270,6,6);//was 23
  wait(0.4,seconds);
  robot.drive_to_point(0, 0,12,12);
  //Intake.stop();

  //score preload
  robot.swing_speed_scalar(-44, 180, 12, 0.5, true);
  robot.turn_to_angle(180,12);
  robot.drive_distance(-13,180,12,12,robot.drive_settle_error,0,700);

  //score ball in intake
  robot.drive_distance(7,180,12,12);
  robot.turn_to_angle(0,12);
  Intake.spin(reverse,100,percent);
  wait(0.4,seconds);
 
  //give them a little tap
  Intake.stop();
  robot.drive_distance(7,0,12,12,robot.drive_settle_error,robot.drive_settle_time,300);
  robot.drive_distance(-6,0,12,12);
 

  //go for first mid triball
  robot.turn_to_angle(270,12);
  Intake.spin(forward,100,percent);
  robot.drive_distance(52,285);

  //spit the triball twoards goal
  robot.drive_distance(-12);
  robot.turn_to_angle(59,12);//was 63
  Intake.spin(reverse,100,percent); //was 63
  wait(0.8,seconds);
  Intake.stop();

  //go for second mid triball
  Intake.spin(forward,100,percent);
  robot.drive_distance(32,344,6,6); //was 30,355
  wait(0.8,seconds);

  robot.turn_to_angle(90,12);
  Intake.spin(reverse,100,percent);
  Wings.set(true);
  robot.drive_distance(16,90,12,12);
  robot.drive_distance(-10,90,12,12);
  Intake.stop();
  robot.drive_distance(15,90,12,12);
    robot.drive_distance(-10,90,12,12);


}

//scores 3 and touches bar
void Far_Score_Touch(){ 
  
  robot.set_coordinates(0, 0, 270); //odom/drive things
  default_constants();

  //grab triball under bar
  Intake.spin(forward,100,percent);
  robot.drive_distance(20,270,12,12);
  Intake.stop();
  
  //line up for descore
  robot.drive_distance(-43,270); 
  robot.turn_to_angle(45);
  robot.drive_distance(9,60,12,12);

  //descore
  wait(0.5,sec);
  Wings.set(true);
  robot.right_swing_to_angle(0,12,robot.swing_settle_error,robot.swing_settle_time,700,robot.swing_kp,robot.swing_ki,robot.swing_kd,robot.swing_starti);
  
  //score the 3
  Intake.spin(reverse,100,percent);
  wait(0.4,seconds);
  Wings.set(false);
  Intake.stop();
  robot.turn_to_angle(215);
  robot.drive_distance(-20,195,12,12,robot.drive_settle_error,robot.drive_settle_time,500);
  
  //go touch
  robot.drive_distance(30,225);
  Wings.set(true);
  robot.drive_distance(41,270);

}

//touch + score + desc (brings to side) !WP!
void Close_Score_Desc_Touch(){
  
  robot.set_coordinates(0, 0, 0); //odom and drive constant things
  robot.set_drive_constants(12, 4, 0, 20, 0);
  
  //go score the preload in opp goal
  robot.swing_speed_scalar(25, 315, 12, 0.5, true);
  robot.swing_speed_scalar(15, 0, 12, 0.5, false);
  Intake.spin(reverse,100,percent);
  wait(0.5,seconds);
  Intake.stop();
  robot.drive_distance(2);
  robot.drive_distance(-2);

  //line up and descore
  robot.swing_speed_scalar(-25, 315, 6.5, 0.35, true);
  wait(0.5,sec);
  Wings.set(true);
  robot.swing_speed_scalar(-15, 270, 12, 0.1, false);
  Wings.set(false);

  //get robot in position for touch
  robot.drive_distance(7);
  robot.turn_to_angle(135);
  robot.drive_distance(-12);
  robot.drive_distance(3);

  //go touch
  robot.drive_distance(26, 90, 11, 5);
  Wings.set(true);
  robot.drive_distance(22);

}

//descores, then shoots over barrier, then touches. not used currently, kinda useless
void Close_Desc_Shoot_Touch(){

  robot.set_coordinates(0, 0, 315); //odom things

  //descore
  robot.drive_distance(8,315);
  Wings.set(true);
  robot.swing_speed_scalar(9, 90, 4, 0.5, false);
  Wings.set(false);

  //shoot triball over barrier
  robot.turn_to_angle(65);
  PunchMotor.setVelocity(100, percent);
  PunchMotor.spinFor(forward, -2.938, turns);
  
  robot.set_drive_constants(12, 1.5, 0, 10, 0); //change p constant for touching
  
  //go touch
  robot.turn_to_point(0,0);
  robot.drive_to_point(6, -8.5);
  Controller1.Screen.print(robot.odom.X_position);
  Controller1.Screen.print(" ");
  Controller1.Screen.print(robot.odom.Y_position);
  robot.turn_to_angle(90);
  robot.drive_distance(45);  

}

//Do Nothing (idk, might be useful sometime?)
void Sit(){} 

//vision code function (not commenting this)
void VisionChase(float speed, float pturn, float pdrive, vex::vision::signature vis, float timeout, float lungedist){
  Vision21.takeSnapshot(vis); 
  if(Vision21.objects[0].exists){
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
        return;
      }
    }
  }
}

////Other functions are for debugging////

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



