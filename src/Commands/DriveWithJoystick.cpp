#include "DriveWithJoystick.h"


DriveWithJoystick::DriveWithJoystick()
    : frc::Command("DriveWithJoystick") {
	Requires(&Robot::drivetrain);
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
	double x = Robot::joystick->GetX();
	double y = Robot::joystick->GetY();
	double v = (1-abs(x)) * (y) + y;
	double w = (1-abs(y)) * (x) + x;
	double r = (v+w) /2;
	double l = (v-w)/2;
	Robot::drivetrain.Drive(l, r);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystick::End() {
	Robot::drivetrain.Drive(0, 0);
}
