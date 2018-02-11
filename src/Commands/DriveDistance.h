/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>
#include <PIDController.h>

class DriveDistance : public frc::Command, frc::PIDSource, frc::PIDOutput {
public:
	double inchesToDrive;
	
	DriveDistance(double inchesToDrive): inchesToDrive(inchesToDrive) {};
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	
	double PIDGet() override;
	void PIDWrite() override;

private:
	double powerRampupCounter = 0;
	double startingAngle = 0;

	double turningValue = 0;

	frc::PIDController turnPid{ 0.05, 0.002, this, this };
};
