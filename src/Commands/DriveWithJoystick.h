/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>
#include <OI.h>
#include <Joystick.h>
#include <RobotMap.h>

#include "../Robot.h"

class DriveWithJoystick : public frc::Command {
public:
	void SetControlScheme(joystickMode);
	DriveWithJoystick();
	void Execute() override;
	bool IsFinished() override;
	void End() override;
};
