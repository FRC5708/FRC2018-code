/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/ClawWithJoystick.h>
#include "Robot.h"
#include "WPILib.h"
#include <PowerDistributionPanel.h>
#include <Commands/DriveWithJoystick.h>
#include <Commands/WinchWithJoystick.h>

#include <chrono>
#include <thread>

Drivetrain Robot::drivetrain;
Arm Robot::arm;
Winch Robot::winch;
Claw Robot::claw;
Wrist Robot::wrist;
Joystick* Robot::joystick;
Gyro* Robot::gyro;
JoystickMode Robot::joyMode = SINGLE_JOY;
Compressor* compressor;


void setupObjectiveChooser(frc::SendableChooser<AutonMode>* chooser, std::string name) {

	// space in beginning for alphabetical ordering
	chooser->AddDefault(" " + name + " default: Cross line", AutonMode::crossLine);
	chooser->AddObject("do nothing", AutonMode::nothing);
	chooser->AddObject("Switch (either)", AutonMode::eitherSwitch);
	chooser->AddObject("Switch (left)", AutonMode::leftSwitch);
	chooser->AddObject("Switch (right)", AutonMode::rightSwitch);
	chooser->AddObject("Switch (side)", AutonMode::sideSwitch);
	//chooser->AddObject("Scale (either)", AutonMode::eitherScale);
	//chooser->AddObject("Scale (left)", AutonMode::leftScale);
	//chooser->AddObject("Scale (right)", AutonMode::rightScale);
	frc::SmartDashboard::PutData(name, chooser);
}
void Robot::RobotInit() {


	Robot::joystick = new Joystick(0);
	Robot::gyro = new ADXRS450_Gyro();
	Robot::gyro->Reset();

	drivetrain.leftEncoder->Reset();
	drivetrain.rightEncoder->Reset();
	winch.encoder.Reset();

	//m_chooser.AddDefault("Cross line", { AutonMode::crossLine });
	//frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

	location_select.AddDefault("Left", 'L');
	location_select.AddObject("Center", 'C');
	location_select.AddObject("Right", 'R');
	frc::SmartDashboard::PutData("Location", &location_select);

	compressor = new Compressor(0);
	compressor->SetClosedLoopControl(true);
  
	setupObjectiveChooser(&primary_objective_select, "Primary Obj.");
	setupObjectiveChooser(&secondary_objective_select, "Secondary Obj.");
	setupObjectiveChooser(&tertiary_objective_select, "Tertiary Obj.");

	control_scheme_select.AddDefault("Xbox", XBOX);
	control_scheme_select.AddObject("Joystick", SINGLE_JOY);
	frc::SmartDashboard::PutData("Control Scheme", &control_scheme_select);

	switch_scale_select.AddDefault("Left", 'L');
	switch_scale_select.AddObject("Right", 'L');
	
	wrist_helper_select.AddDefault("Keep grabber within frame", true);
	wrist_helper_select.AddObject("Disable functionality", false);

    CameraServer::GetInstance()->StartAutomaticCapture();
}

void Robot::AllPeriodic() {
    frc::Scheduler::GetInstance()->Run();
	//arm.wristHelping = wrist_helper_select.GetSelected();
	LogSensors();
	
	constexpr int compressorStopTicks = 50; // one second
	static int compressorStopCount = 0;
	static bool compressorStopped = false;
	
	if (DriverStation::GetInstance().GetBatteryVoltage() < 10.0 && !compressorStopped) {
		compressor->Stop();
		compressorStopCount = 0;
		compressorStopped = true;
	}
	else {
		++compressorStopCount;
		if (compressorStopped && compressorStopCount >= compressorStopTicks) {
			compressor->Start();
			compressorStopped = false;
		}
	}
}

void Robot::DisabledPeriodic(){
    AllPeriodic();
}

void Robot::LogSensors() {
	SmartDashboard::PutNumber("left encoder (revolutions)", drivetrain.leftEncoder->GetDistance());
	SmartDashboard::PutNumber("right encoder (revolutions)", drivetrain.rightEncoder->GetDistance());
	
	SmartDashboard::PutNumber("encoder distance (inches)", drivetrain.GetDistance());
	SmartDashboard::PutNumber("gyro rotation (degrees)", Robot::gyro->GetAngle());
	SmartDashboard::PutNumber("gyro rotation (rate)", Robot::gyro->GetRate());
	SmartDashboard::PutNumber("Encoder 4 data(distance)", Robot::winch.encoder.GetDistance());
	SmartDashboard::PutNumber("Total Current", PowerDistributionPanel(0).GetTotalCurrent());
}

void Robot::AutonomousInit() {
    
    // switch and scale location
    // https://wpilib.screenstepslive.com/s/currentCS/m/getting_started/l/826278-2018-game-data-details
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    
    // for testing
    //gameData = "LLL";

    char location = (char) location_select.GetSelected();
    AutonMode primary_objective = (AutonMode) primary_objective_select.GetSelected();
    AutonMode secondary_objective = (AutonMode) secondary_objective_select.GetSelected();
    AutonMode tertiary_objective = (AutonMode) secondary_objective_select.GetSelected();
    

    m_autonomousCommand = std::unique_ptr<AutoCommand>(new AutoCommand(
                          location, gameData, { primary_objective, secondary_objective, tertiary_objective }));
    
    m_autonomousCommand->Start();
    //frc::Scheduler::GetInstance()->AddCommand(&*m_autonomousCommand);
}

void Robot::AutonomousPeriodic() {
    AllPeriodic();
}

void Robot::TeleopInit(){
    // This makes sure that the autonomous stops running when
    // teleop starts running. If you want the autonomous to
    // continue until interrupted by another command, remove
    // this line or comment it out.

	control_scheme = (JoystickMode) control_scheme_select.GetSelected();

    if (m_autonomousCommand != nullptr) {
        m_autonomousCommand->Cancel();
        m_autonomousCommand = nullptr;
        
        arm.CancelMoveTo();
    }
    driveCommand = new DriveWithJoystick();
    clawCommand = new ClawWithJoystick();
    winchCommand = new WinchWithJoystick();

    Robot::joyMode = control_scheme;
  
    driveCommand->Start();
    clawCommand->Start();
    winchCommand->Start();

    //Remove when done testing!!!!!


}

void Robot::TeleopPeriodic() {
    AllPeriodic();
}

START_ROBOT_CLASS(Robot);
