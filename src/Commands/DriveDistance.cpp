/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


constexpr double powerRampupSpeed = 0.5; // seconds
constexpr double powerLimit = 0.5;
constexpr double ticksPerSecond = 50;
constexpr double powerRampdownDist = 6; // inches
constexpr double minPower = 0.1;

#include <Commands/DriveDistance.h>
#include "Robot.h"
#include "RobotMap.h"
#include <iostream>
#include <math.h>


// Called just before this Command runs the first time
void DriveDistance::Initialize() {
	//Robot::gyro->Reset();
	startingAngle = Robot::gyro->GetAngle();
	Robot::drivetrain.ResetDistance();
	
	std::cout << "driving distance: " << inchesToDrive << " inches" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute() {
	powerRampupCounter += powerRampupSpeed/ticksPerSecond;
	
	double power = std::min(powerLimit, powerRampupCounter * powerLimit);
	power = std::min(power, Robot::drivetrain.GetDistance() / powerRampdownDist);
	power = std::max(power, minPower);
	
	if (inchesToDrive < 0) power = -power;
	
	double turningValue = (Robot::gyro->GetAngle() - startingAngle) * 0.05;
	Robot::drivetrain.DrivePolar(power, turningValue);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished() {
	double distance = Robot::drivetrain.GetDistance();
	
	if (inchesToDrive > 0) return distance >= inchesToDrive;
	else return distance <= inchesToDrive;
}

// Called once after isFinished returns true
void DriveDistance::End() {
	Robot::drivetrain.Drive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted() { End(); }
