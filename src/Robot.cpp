/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "WPILib.h"
Drivetrain Robot::drivetrain;
Claw Robot::claw;
OI Robot::oi;
Joystick* Robot::joystick;
Gyro* Robot::gyro;
joystickMode Robot::joyMode = SINGLE_JOY;
Compressor* compressor;


void setupObjectiveChooser(frc::SendableChooser<AutonMode>* chooser, std::string name) {

	chooser->AddDefault("Cross the line", AutonMode::crossLine);
	chooser->AddObject("Switch (either)", AutonMode::eitherSwitch);
	chooser->AddObject("Switch (left)", AutonMode::leftSwitch);
	chooser->AddObject("Switch (right)", AutonMode::rightSwitch);
	chooser->AddObject("Scale", AutonMode::eitherScale);
	frc::SmartDashboard::PutData(name, chooser);
}
void Robot::RobotInit() {

	Robot::joystick = new Joystick(0);
	Robot::gyro = new ADXRS450_Gyro();

	//m_chooser.AddDefault("Cross line", { AutonMode::crossLine });
	//frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

	location_select.AddDefault("Left", 'L');
	location_select.AddObject("Center", 'C');
	location_select.AddObject("Right", 'R');
	frc::SmartDashboard::PutData("Location", &location_select);

	compressor = new Compressor(0);
	compressor->SetClosedLoopControl(true);
  
	setupObjectiveChooser(&primary_objective_select, "Primary Objective");
	setupObjectiveChooser(&secondary_objective_select, "Secondary Objective");

	control_scheme_select.AddDefault("Xbox", XBOX);
	control_scheme_select.AddObject("Joystick", SINGLE_JOY);
	frc::SmartDashboard::PutData("Control Scheme", &control_scheme_select);
}


void Robot::DisabledPeriodic(){
    frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit(){
    
    // switch and scale location
    // https://wpilib.screenstepslive.com/s/currentCS/m/getting_started/l/826278-2018-game-data-details
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    

    char location = (char) location_select.GetSelected();
    AutonMode primary_objective = (AutonMode) primary_objective_select.GetSelected();
    AutonMode secondary_objective = (AutonMode) secondary_objective_select.GetSelected();
    

    m_autonomousCommand = std::unique_ptr<MyAutoCommand>(new MyAutoCommand(
                          location, gameData, { primary_objective, secondary_objective }));
    
    m_autonomousCommand->Start();
    //frc::Scheduler::GetInstance()->AddCommand(&*m_autonomousCommand);
}

void Robot::AutonomousPeriodic(){
    frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit(){
    // This makes sure that the autonomous stops running when
    // teleop starts running. If you want the autonomous to
    // continue until interrupted by another command, remove
    // this line or comment it out.

	control_scheme = (joystickMode) control_scheme_select.GetSelected();

    if (m_autonomousCommand != nullptr) {
        m_autonomousCommand->Cancel();
        m_autonomousCommand = nullptr;
    }
    driveCommand = new DriveWithJoystick();
    clawCommand = new ClawWithJoystick();

    Robot::joyMode = control_scheme;
  
    driveCommand->Start();
    clawCommand->Start();
}

void Robot::TeleopPeriodic() {
    frc::Scheduler::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);
