/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>

class DriveDistance : public frc::Command {
public:
	double inchesToDrive;
	double startingAngle = 0;
	
	DriveDistance(double inchesToDrive): inchesToDrive(inchesToDrive) {};
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	
	double powerRampupCounter = 0;
};
