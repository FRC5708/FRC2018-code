/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;


constexpr int FLMotorChannel = 0;
constexpr int BLMotorChannel = 1;
constexpr int FRMotorChannel = 2;
constexpr int BRMotorChannel = 3;

constexpr int ArmMotorChannel1 = 10;
constexpr int ArmMotorChannel2 = 10;

constexpr int intakeMotorChannel1 = 4;
constexpr int intakeMotorChannel2 = 5;


constexpr int leftWinchMotorChannel = 6;
constexpr int rightWinchMotorChannel = 7;

constexpr int ArmReleaseChannel = 8;

constexpr int LeftEncoderChannel[2] = {0,1};
constexpr int RightEncoderChannel[2] = {2,3};

constexpr int ArmEncoderChannel[2] = {4,5};

constexpr int ClawSolenoid1Channel[2] = {0,1};
constexpr int ClawSolenoid2Channel[2] = {4,5};
constexpr int WristSolenoidChannel[2] = {2,3};

constexpr int gyroChannel = 1;

constexpr double WheelCircumference = 6 * M_PI;

// in inches. 
constexpr double fieldWidth = 360;
//change these
constexpr double robotLength = 31.9, robotWidth = 27.5;


enum joystickMode {SINGLE_JOY, XBOX};
