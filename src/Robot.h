#ifndef Robot_H
#define Robot_H

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TimedRobot.h>
#include <DriverStation.h>
#include <OI.h>
#include <Joystick.h>
#include "WPILib.h"


#include <Subsystems/Drivetrain.h>

#include <Commands/DriveWithJoystick.h>


class Robot : public frc::TimedRobot {
public:
	static Drivetrain drivetrain;
	static OI oi;
	static Joystick* joystick;

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
	frc::Command* m_autonomousCommand = nullptr;
	//DriveWithJoystick driveCommand;
	frc::SendableChooser<frc::Command*> m_chooser;
};

#endif