/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

Drivetrain Robot::drivetrain;
OI Robot::oi;

void Robot::RobotInit() {
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}


void Robot::DisabledPeriodic(){
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit(){
	
	// switch and scale location
	// https://wpilib.screenstepslive.com/s/currentCS/m/getting_started/l/826278-2018-game-data-details
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
}

void Robot::AutonomousPeriodic(){
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit(){
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Cancel();
		m_autonomousCommand = nullptr;
	}
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	//driveCommand.Start();
}

START_ROBOT_CLASS(Robot);
