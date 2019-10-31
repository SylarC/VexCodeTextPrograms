// Auto Setup
  // ---- START VEXCODE CONFIGURED DEVICES ----
  // Robot Configuration:
  // [Name]               [Type]        [Port(s)]
  // Controller1          controller                    
  // LFMotor              motor         1               
  // RFMotor              motor         2               
  // LBMotor              motor         9               
  // RBMotor              motor         10              
  // leftRoller           motor         3               
  // rightRoller          motor         8               
  // armMotor             motor         5               
  // trayMotor            motor         4               
  // ---- END VEXCODE CONFIGURED DEVICES ----
  /*----------------------------------------------------------------------------*/
  /*                                                                            */
  /*    Module:       main.cpp                                                  */
  /*    Author:       Ky                                                      */
  /*    Created:      Thu Sep 26 2019                                           */
  /*    Description:  Competition Template                                      */
  /*                                                                            */
  /*----------------------------------------------------------------------------*/

  // ---- START VEXCODE CONFIGURED DEVICES ----
  // Robot Configuration:
  // [Name]               [Type]        [Port(s)]
  // Controller1          controller                    
  // LFMotor              motor         1               
  // RFMotor              motor         2               
  // LBMotor              motor         9               
  // RBMotor              motor         10              
  // leftRoller           motor         3               
  // rightRoller          motor         8               
  // armMotor             motor         5               
  // trayMotor            motor         4               
  // ---- END VEXCODE CONFIGURED DEVICES ----

// Config
  //**********************************//
  #include "vex.h"
  using namespace vex;
  // A global instance of competition
  competition Competition;
  //**********************************//
// Variable Declaration:
enum TeamColor {Red = 1, Blue = 0}; 
enum AutonPos {RedHomeTower = 1, BlueHomeTower = 2, RedProtGoal = 3, BlueProtGoal = 4};
int startingArea = 1;

//  MOTOR MOVE FUNCTIONS
  // Roller Functions
  void rollerIn(){
    leftRoller.setVelocity(100, percent);
    rightRoller.setVelocity(100, percent);
  }
  void rollerOut(){
    leftRoller.setVelocity(-100, percent);
    rightRoller.setVelocity(-100, percent);
  }
  void rollerStop(){
    rightRoller.setStopping(brake);
    leftRoller.setStopping(brake);
    rightRoller.stop();
    leftRoller.stop();
  }
  // Arm Functions
  void armUp(){
    armMotor.spin(forward);
  }
  void armDown(){
    armMotor.spin(reverse);
  }
  void armStop(){
    armMotor.setStopping(hold);
    armMotor.stop();
  }
  // Tray Functions
  void trayOut(){
    trayMotor.setVelocity(-100, percent);
  }
  void traySlowOut(){
    trayMotor.setVelocity(-25, percent);
  }
  void trayIn(){
    trayMotor.setVelocity(100, percent);
  }

  void traySlowIn(){
    trayMotor.setVelocity(25, percent);
  }

  void trayStop(){
    trayMotor.setStopping(brake);
    trayMotor.stop();
  }

void cycleStartingArea(){
  if(startingArea == 4){
    startingArea = 1;
  }
  else{
  startingArea += 1;
  }
}

int activeBrainScreen(){
  while(true){
    Controller1.ButtonA.pressed(cycleStartingArea);
    Brain.Screen.clearLine();
    switch(startingArea){
      case(RedHomeTower):
        Brain.Screen.print("Starting Area 1, Red Home Tower Side");
        break;
      case(BlueHomeTower):
        Brain.Screen.print("Starting Area 2, Blue Home Tower Side");
        break;
      case(RedProtGoal):
        Brain.Screen.print("Starting Area 3, Red Protected Goal Side");
        break;
      case(BlueProtGoal):
        Brain.Screen.print("Starting Area 4, Blue Protected Goal Side");
        break;
      default:
        break;
    }
    wait(0.1, seconds);
    if(Controller1.ButtonX.pressing()){
      Brain.Screen.newLine();
      Brain.Screen.print("Selected!");
      break;
    }
  }
  return startingArea;
}

void pre_auton(void) {
  // Initializing Robot Configuration
  vexcodeInit();
  activeBrainScreen();
}

void setBaseVelocity(int velocity){
  RFMotor.setVelocity(velocity, percent);
  RBMotor.setVelocity(velocity, percent);
  LFMotor.setVelocity(velocity, percent);
  LBMotor.setVelocity(velocity, percent);
}


//  ROBOT MOVE FUNCTIONS
void driveRobot(float value, char type){
  if(type == 'd'){
    RFMotor.spinFor(value, degrees, false);
    RBMotor.spinFor(value, degrees, false);
    LFMotor.spinFor(value, degrees, false);
    LBMotor.spinFor(value, degrees);
  }
  else if(type == 't'){
    RFMotor.spinFor(value, turns, false);
    RBMotor.spinFor(value, turns, false);
    LFMotor.spinFor(value, turns, false);
    LBMotor.spinFor(value, turns);
  }
  RFMotor.setStopping(brake);
  RBMotor.setStopping(brake);
  LFMotor.setStopping(brake);
  LBMotor.setStopping(brake);
  RFMotor.stop();
  RBMotor.stop();
  LFMotor.stop();
  LBMotor.stop();
  wait(0.2, seconds);
}

void turnRobot(float value, char type, char direction){
  if(direction == 'r'){
    if(type == 'd'){
      RFMotor.spinFor(-value, degrees, false);
      RBMotor.spinFor(-value, degrees, false);
      LFMotor.spinFor(value, degrees, false);
      LBMotor.spinFor(value, degrees);
    }
    else if(type == 't'){
      RFMotor.spinFor(-value, turns, false);
      RBMotor.spinFor(-value, turns, false);
      LFMotor.spinFor(value, turns, false);
      LBMotor.spinFor(value, turns);
    }
  }
  else if(direction == 'l'){
    if(type == 'd'){
      RFMotor.spinFor(value, degrees, false);
      RBMotor.spinFor(value, degrees, false);
      LFMotor.spinFor(-value, degrees, false);
      LBMotor.spinFor(-value, degrees);
    }
    else if(type == 't'){
      RFMotor.spinFor(value, turns, false);
      RBMotor.spinFor(value, turns, false);
      LFMotor.spinFor(-value, turns, false);
      LBMotor.spinFor(-value, turns);
    }
  }
  RFMotor.setStopping(brake);
  RBMotor.setStopping(brake);
  LFMotor.setStopping(brake);
  LBMotor.setStopping(brake);
  RFMotor.stop();
  RBMotor.stop();
  LFMotor.stop();
  LBMotor.stop();
  wait(0.2, seconds);
}

// AUTON FUNCTIONS
void homeTowerSide(TeamColor teamColor){
  int direction = 1;
  if(teamColor == Blue){
    direction = -1;
  }
  // Start spinners
  leftRoller.setVelocity(75, percent);
  leftRoller.spin(forward);
  rightRoller.spin(forward);
  // Move forward and pick up the 4 cubes
  setBaseVelocity(30);
  driveRobot(3.4, 't');
  // Turn to face scoring zone
  // *** Original Line:
  // turnRobot(470, 'd', 'r');
  turnRobot(470*direction, 'd', 'r');
  // Move forward to move to scoring zone
  setBaseVelocity(45);
  driveRobot(3.25, 't');
  // Stop spinners
  rollerStop();
  // Roll spinners out a little
  leftRoller.spinFor(-270, degrees, false);
  rightRoller.spinFor(-270, degrees);
  // Score tray
  trayMotor.setVelocity(75, percent);
  trayMotor.spinFor(-500, degrees);
  trayMotor.setVelocity(30, percent);
  trayMotor.spinFor(-50, degrees);
  trayMotor.setStopping(hold);
  trayMotor.stop();
  wait(0.2, seconds);
  driveRobot(25, 'd');
  // Back up and move spinners out
  leftRoller.setVelocity(50, percent);
  rightRoller.setVelocity(50, percent);
  leftRoller.spin(reverse);
  rightRoller.spin(reverse);
  setBaseVelocity(10);
  wait(0.5, seconds);
  driveRobot(-2.0, 't');
}

void protGoalSide(TeamColor teamColor){
  Brain.Screen.newLine();
}

void autonomous(void) {
  switch(startingArea){
    case(RedHomeTower):
      homeTowerSide(Red);
      break;
    case(BlueHomeTower):
      homeTowerSide(Blue);
      break;
    case(RedProtGoal):
      protGoalSide(Red);
      break;
    case(BlueProtGoal):
      protGoalSide(Blue);
      break;
  }
}



void usercontrol(void) {
  // threshold stops the motors when Axis values are close to zero.
  int threshold = 5;
 
  while (true) {
  /** Drive Base Code **/
    // Get the velocity percentage of the left motor. (Axis3)
    int leftSideSpeed = Controller1.Axis3.position();
    // Get the velocity percentage of the right motor. (Axis2)
    int rightSideSpeed = Controller1.Axis2.position();

    // Set the speed of the left motor. If the value is less than the threshold,
    // set it to zero.
    if (abs(leftSideSpeed) < threshold) {
      // Set the speed to zero.
      LFMotor.setVelocity(0, percent);
      LBMotor.setVelocity(0, percent);
    } 
    else {
      // Set the speed to leftSideSpeed
      LFMotor.setVelocity(leftSideSpeed, percent);
      LBMotor.setVelocity(leftSideSpeed, percent);
    }
    // Set the speed of the right motor. If the value is less than the threshold,
    // set it to zero.
    if (abs(rightSideSpeed) < threshold) {
      // Set the speed to zero
      RFMotor.setVelocity(0, percent);
      RBMotor.setVelocity(0, percent);
    }
    else {
      // Set the speed to rightSideSpeed
      RFMotor.setVelocity(rightSideSpeed, percent);
      RBMotor.setVelocity(rightSideSpeed, percent);
    }
    RFMotor.spin(forward);
    LFMotor.spin(forward);
    RBMotor.spin(forward);
    LBMotor.spin(forward);

  /** Roller Code **/
    rightRoller.spin(forward);
    leftRoller.spin(forward);
    Controller1.ButtonR1.pressed(rollerIn);
    Controller1.ButtonR2.pressed(rollerOut);
    if(Controller1.ButtonR1.pressing() == false && Controller1.ButtonR2.pressing() == false){
      rollerStop();
    }
  /** Arm Code **/
    Controller1.ButtonL1.pressed(armUp);
    Controller1.ButtonL2.pressed(armDown);
    if(Controller1.ButtonL1.pressing() == false && Controller1.ButtonL2.pressing() == false){
      armStop();
    }
  /** Tray Code **/
    trayMotor.spin(forward);
    Controller1.ButtonRight.pressed(trayIn);
    Controller1.ButtonLeft.pressed(trayOut);
    Controller1.ButtonUp.pressed(traySlowOut);
    Controller1.ButtonDown.pressed(traySlowIn);
    if(Controller1.ButtonRight.pressing() == false && Controller1.ButtonLeft.pressing() == false && Controller1.ButtonUp.pressing() == false && Controller1.ButtonDown.pressing() == false){
      trayStop();
    }

  }
  wait(20, msec); // Sleep the task for a short amount of time
}

int main(){
  // Run the pre-autonomous function.
  Brain.Screen.clearScreen();
  pre_auton();
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Auton and op-control
  autonomous();
  usercontrol();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
