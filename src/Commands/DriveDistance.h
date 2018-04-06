/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>
#include <PIDController.h>
#include <PIDOutput.h>

class DriveDistance : public frc::Command, frc::PIDSource, frc::PIDOutput {
public:
	double inchesToDrive;
	double timeout; // in seconds
	
	DriveDistance(double inchesToDrive, double timeout = INFINITY): inchesToDrive(inchesToDrive), timeout(timeout) {};
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	
	double PIDGet() override;
	void PIDWrite(double turningValue) override;

private:
	double powerRampupCounter = 0;
	double startingAngle = 0;

	double turningValue = 0;

	frc::PIDController turnPid{ 0.05, 0.001, 0, this, this, 0.02 };
	
	std::chrono::steady_clock::time_point startTime;
};
