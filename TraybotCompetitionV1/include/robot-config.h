using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LFMotor;
extern motor RFMotor;
extern motor LBMotor;
extern motor RBMotor;
extern motor leftRoller;
extern motor rightRoller;
extern motor armMotor;
extern motor trayMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );