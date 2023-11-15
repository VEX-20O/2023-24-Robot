using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor DriveL1;
extern motor DriveL2;
extern motor DriveL3;
extern motor DriveR1;
extern motor DriveR2;
extern motor DriveR3;
extern inertial Inertial11;
extern controller Controller1;
extern digital_out Wings;
extern motor PunchMotor;
extern signature Vision21__GO;
extern signature Vision21__SIG_2;
extern signature Vision21__SIG_3;
extern signature Vision21__SIG_4;
extern signature Vision21__SIG_5;
extern signature Vision21__SIG_6;
extern signature Vision21__SIG_7;
extern vision Vision21;
extern motor Intake;
extern digital_out Blocker;
extern digital_out Climb;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );