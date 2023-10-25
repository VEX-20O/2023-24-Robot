using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor DriveL1;
extern motor DriveL2;
extern motor DriveL3;
extern motor DriveR1;
extern motor DriveR2;
extern motor DriveR3;
extern inertial Inertial7;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );