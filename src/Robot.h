#ifndef Robot_H
#define Robot_H

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TimedRobot.h>
#include <DriverStation.h>
#include <Joystick.h>
#include <RobotMap.h>
#include <Joystick.h>
#include <AnalogGyro.h>
#include <Commands/AutoCommand.h>
#include <Misc.h>
#include "WPILib.h"


#include <Subsystems/Drivetrain.h>
#include <Subsystems/Claw.h>
#include <Subsystems/Winch.h>
#include "Subsystems/Arm.h"
#include "Subsystems/Wrist.h"

class Robot : public frc::TimedRobot {
public:
	static Drivetrain drivetrain;
	static Claw claw;
	static Arm arm;
	static Wrist wrist;
	static Winch winch;
	static Joystick* joystick;
	static Gyro* gyro;
	static joystickMode joyMode;

	std::string gameData;

	void RobotInit() override;

	/**
		 * This function is called once each time the robot enters Disabled
		 * mode.
		 * You can use it to reset any subsystem information you want to clear
		 * when
		 * the robot is disabled.
	*/
	void DisabledInit() override {};
	void DisabledPeriodic() override;

	/**
		 * This autonomous (along with the chooser code above) shows how to
		 * select
		 * between different autonomous modes using the dashboard. The sendable
		 * chooser code works with the Java SmartDashboard. If you prefer the
		 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
		 * GetString code to get the auto name from the text box below the Gyro.
		 *
		 * You can add additional auto modes by adding additional commands to
		 * the
		 * chooser code above (like the commented example) or additional
		 * comparisons
		 * to the if-else structure below with additional strings & commands.
	*/
	void AutonomousInit() override;
	void AutonomousPeriodic() override;

	void TeleopInit() override;
	void TeleopPeriodic() override;

	void TestPeriodic() override {};

private:
	// Have it null by default so that if testing teleop it
	// doesn't have undefined behavior and potentially crash.
	std::unique_ptr<AutoCommand> m_autonomousCommand = nullptr;
	frc::SendableChooser<char> location_select;
	frc::SendableChooser<AutonMode> primary_objective_select;
	frc::SendableChooser<AutonMode> secondary_objective_select;
	frc::SendableChooser<joystickMode> control_scheme_select;

	frc::SendableChooser<char> switch_scale_select;
	frc::SendableChooser<bool> wrist_helper_select;
  
	frc::Command* driveCommand;
	frc::Command* clawCommand;
	frc::Command* winchCommand;
  
	joystickMode control_scheme;
	
	void LogSensors();
	void CheckDashboardOptions();
};

#endif
