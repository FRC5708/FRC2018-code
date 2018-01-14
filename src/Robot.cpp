/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

Drivetrain Robot::drivetrain;
OI Robot::oi;
Joystick* Robot::joystick;

void Robot::RobotInit() {

	Robot::joystick = new frc::Joystick(0);

  m_chooser.AddDefault("Cross line", { AutonMode::crossLine });
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

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
