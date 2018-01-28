/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "WPILib.h"

Drivetrain Robot::drivetrain;
OI Robot::oi;
Joystick* Robot::joystick;
Gyro* Robot::gyro;

void Robot::RobotInit() {

	Robot::joystick = new Joystick(0);
	Robot::gyro = new AnalogGyro(1);

	m_chooser.AddDefault("Cross line", { AutonMode::crossLine });
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

	location_select.AddDefault("Left", 0);
	location_select.AddObject("Middle", 1);
	location_select.AddObject("Right", 2);
	frc::SmartDashboard::PutData("Location", &location_select);


	primary_objective_select.AddDefault("Switch", 0);
	primary_objective_select.AddObject("Scale", 1);
	primary_objective_select.AddObject("Cross the line", 2);
	frc::SmartDashboard::PutData("Primary Objective", &primary_objective_select);

	secondary_objective_select.AddDefault("Switch", 0);
	secondary_objective_select.AddObject("Scale", 1);
	secondary_objective_select.AddObject("Cross the line", 2);
	frc::SmartDashboard::PutData("Secondary Objective", &secondary_objective_select);

	control_scheme_select.AddDefault("Xbox", 0);
	control_scheme_select.AddObject("Joystick", 1);
	frc::SmartDashboard::PutData("Control Scheme", &control_scheme_select);
}


void Robot::DisabledPeriodic(){
    frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit(){
    
    // switch and scale location
    // https://wpilib.screenstepslive.com/s/currentCS/m/getting_started/l/826278-2018-game-data-details
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    
    m_autonomousCommand = std::unique_ptr<MyAutoCommand>(new MyAutoCommand(
                                                                           'L', gameData, m_chooser.GetSelected()));
    
    m_autonomousCommand->Run();

    int location = (int) location_select.GetSelected();
    int primary_objective = (int) primary_objective_select.GetSelected();
    int secondary_objective = (int) secondary_objective_select.GetSelected();
    int control_scheme = (int) control_scheme_select.GetSelected();
    //Do autonomous logic here

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
    driveCommand = new DriveWithJoystick();
}

void Robot::TeleopPeriodic() {
    frc::Scheduler::GetInstance()->Run();
    driveCommand->Start();
}

START_ROBOT_CLASS(Robot);
