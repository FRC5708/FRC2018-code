/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TimedRobot.h>


#include "Commands/ExampleCommand.h"
#include "Commands/MyAutoCommand.h"

#include <DriverStation.h>


class Robot : public frc::TimedRobot {
public:
	void RobotInit() override {
		m_chooser.AddDefault("Cross line", { AutonMode::crossLine });
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
	}
	
	

	/**
	 * This function is called once each time the robot enters Disabled
	 * mode.
	 * You can use it to reset any subsystem information you want to clear
	 * when
	 * the robot is disabled.
	 */
	void DisabledInit() override {}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

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
	
	std::string gameData;
	void AutonomousInit() override {
		/*std::string autoSelected = frc::SmartDashboard::GetString(
				"Auto Selector", "Default");
		if (autoSelected == "My Auto") {
			m_autonomousCommand = &m_myAuto;
		} else {
			m_autonomousCommand = &m_defaultAuto;
		}*/
		
		// switch and scale location
		// https://wpilib.screenstepslive.com/s/currentCS/m/getting_started/l/826278-2018-game-data-details 
		gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		
		m_autonomousCommand = std::unique_ptr<MyAutoCommand>(new MyAutoCommand(
				'L', gameData, m_chooser.GetSelected()));
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (m_autonomousCommand != nullptr) {
			m_autonomousCommand->Cancel();
			m_autonomousCommand = nullptr;
		}
	}

	void TeleopPeriodic() override { frc::Scheduler::GetInstance()->Run(); }

	void TestPeriodic() override {}

private:
	// Have it null by default so that if testing teleop it
	// doesn't have undefined behavior and potentially crash.
	std::unique_ptr<MyAutoCommand> m_autonomousCommand = nullptr;
	frc::SendableChooser<std::vector<AutonMode>> m_chooser;
};

START_ROBOT_CLASS(Robot)
