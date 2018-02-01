#include "DriveWithJoystick.h"


DriveWithJoystick::DriveWithJoystick()
    : frc::Command("DriveWithJoystick"){
	Requires(&Robot::drivetrain);
}

void DriveWithJoystick::SetControlScheme(joystickMode control_scheme){
	joyMode=control_scheme;
}
// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
	double turn = 0;
	double power = 0;

	switch (Robot::joyMode){
		case SINGLE_JOY: {
			turn = -Robot::joystick->GetZ();
			power = -Robot::joystick->GetY();
			break;
		}
		case XBOX: {
			turn = Robot::joystick->GetX();
			power = Robot::joystick->GetRawAxis(3)-Robot::joystick->GetRawAxis(2);
			break;
		}
	}
	//Robot::drivetrain.DrivePolar(power, turn);
	double v = (1-abs(turn)) * (power) + power;
	double w = (1-abs(power)) * (turn) + turn;
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
