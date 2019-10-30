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

//**********************************//
#include "vex.h"
using namespace vex;
// A global instance of competition
competition Competition;
//**********************************//


//  MOTOR MOVE FUNCTIONS
  // Roller Functions
  void rollerIn(){
    leftRoller.spin(reverse);
    rightRoller.spin(reverse);
  }
  void rollerOut(){
    leftRoller.spin(forward);
    rightRoller.spin(forward);
  }
  void rollerStop(){
    rightRoller.setStopping(hold);
    leftRoller.setStopping(hold);
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
    trayMotor.spin(forward);
  }
  void traySlowOut(){
    trayMotor.setVelocity(25, percent);
    trayMotor.spin(forward);
  }
  void trayIn(){
    trayMotor.spin(reverse);
  }
  void trayStop(){
    trayMotor.setStopping(hold);
    trayMotor.stop();
  }


void pre_auton(void) {
  // Initializing Robot Configuration
  vexcodeInit();
}

void autonomous(void) {
  trayMotor.setVelocity(50, percent);
  trayMotor.spin(forward);
  wait(1, seconds);
  trayMotor.stop();
  trayMotor.setVelocity(100, percent);
  trayMotor.spin(reverse);
}

void usercontrol(void) {
  // Initializing Robot Configuration.
  vexcodeInit();
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
  

  /** Roller Code **/
    Controller1.ButtonR1.pressed(rollerIn);
    Controller1.ButtonR2.pressed(rollerOut);
    if(Controller1.ButtonR1.pressing() == false && Controller1.ButtonR2.pressing() == false){
      trayStop();
    }
  /** Arm Code **/
    Controller1.ButtonL1.pressed(armUp);
    Controller1.ButtonL2.pressed(armDown);
    if(Controller1.ButtonL1.pressing() == false && Controller1.ButtonL2.pressing() == false){
      armStop();
    }
  /** Tray Code **/
    Controller1.ButtonRight.pressed(trayIn);
    Controller1.ButtonLeft.pressed(trayOut);
    Controller1.ButtonUp.pressed(traySlowOut);
    if(Controller1.ButtonRight.pressing() == false && Controller1.ButtonLeft.pressing() == false && Controller1.ButtonUp.pressing() == false){
      trayStop();
    }

  }
  wait(20, msec); // Sleep the task for a short amount of time
}


int main(){
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
