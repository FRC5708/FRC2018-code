/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


constexpr double powerRampupSpeed = 0.3; // seconds
constexpr double powerLimit = 0.6;
constexpr double ticksPerSecond = 50;
constexpr double powerRampdownTime = 0.3; // seconds remaining IF the robot keeps going the same speed
constexpr double minPower = 0.3;

#include <Commands/DriveDistance.h>
#include "Robot.h"
#include "RobotMap.h"
#include <iostream>
#include <math.h>
#include <chrono>


// Called just before this Command runs the first time
void DriveDistance::Initialize() {
	//Robot::gyro->Reset();
	startingAngle = Robot::gyro->GetAngle();
	Robot::drivetrain.ResetDistance();


	turnPid.SetOutputRange(-0.2, 0.2);
	turnPid.SetSetpoint(startingAngle);
	turnPid.Enable();
	
	startTime = std::chrono::steady_clock::now();

	std::cout << "driving distance: " << inchesToDrive << " inches" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished() {
	if (!std::isinf(timeout) && 
			std::chrono::steady_clock::now() > startTime + std::chrono::microseconds((int) (timeout * 1000000))) {
		return true;
	}
	
	double distance = Robot::drivetrain.GetDistance();

	if (inchesToDrive > 0) return distance >= inchesToDrive;
	else return distance <= inchesToDrive;
}

// Called once after isFinished returns true
void DriveDistance::End() {
	turnPid.Disable();
	Robot::drivetrain.Drive(0, 0);
	std::cout << "ended DriveStraight" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted() { End(); }

double DriveDistance::PIDGet() {
	return Robot::gyro->GetAngle();
}

void DriveDistance::PIDWrite(double turningValue) {
	powerRampupCounter += 1/(powerRampupSpeed*ticksPerSecond);
	double power = std::min(powerLimit, powerRampupCounter * (powerLimit - minPower) + minPower);

	double remainingTime = (inchesToDrive - Robot::drivetrain.GetDistance()) / Robot::drivetrain.GetRate();
	if (remainingTime < 0) remainingTime = 0;
	double rampdownPower = remainingTime / powerRampdownTime  * (powerLimit - minPower) + minPower;
	power = std::min(power, rampdownPower);

	power = std::max(power, minPower);

	if (inchesToDrive < 0) power = -power;


	Robot::drivetrain.DrivePolar(power, turningValue);

	SmartDashboard::PutNumber("DriveDistance power", power);
}




