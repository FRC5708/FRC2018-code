#include "DriveWithJoystick.h"


DriveWithJoystick::DriveWithJoystick()
    : frc::Command("DriveWithJoystick") {
	Requires(&Robot::drivetrain);
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
	//auto& joystick = Robot::oi.GetJoystick();
	//Robot::drivetrain.Drive(-joystick.GetY(), -joystick.GetX());
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystick::End() {
	Robot::drivetrain.Drive(0, 0);
}
