/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/DriveDistance.h>
#include "Robot.h"
#include "RobotMap.h"
#include <iostream>


// Called just before this Command runs the first time
void DriveDistance::Initialize() {
	Robot::gyro->Reset();
	Robot::drivetrain.ResetDistance();
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute() {
	double turningValue = (0 - Robot::gyro->GetAngle()) * 0.05;
	std::cout << turningValue << std::endl;
	Robot::drivetrain.DrivePolar(0.5, -turningValue);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished() {
	// check encoders
	return Robot::drivetrain.GetDistance() > inchesToDrive;
}

// Called once after isFinished returns true
void DriveDistance::End() {
	Robot::drivetrain.Drive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted() { End(); }
