#include "DriveWithJoystick.h"


DriveWithJoystick::DriveWithJoystick()
    : frc::Command("DriveWithJoystick"){
	Requires(&Robot::drivetrain);
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
	double turn = 0;
	double power = 0;
	double arm_power = 0;

	switch (Robot::joyMode){
		case SINGLE_JOY: {
			turn = -Robot::joystick->GetX();
			power = Robot::joystick->GetY();
			arm_power = ((Robot::joystick->GetRawButtonPressed(5) ? 1 : 0) + (Robot::joystick->GetRawButtonPressed(6) ? -1 : 0));


			break;
		}
		case XBOX: {
			turn = Robot::joystick->GetX();
			power = Robot::joystick->GetRawAxis(3)-Robot::joystick->GetRawAxis(2);
			break;
		}
	}
	//Robot::drivetrain.DrivePolar(power, turn);
	double v = (1-fabs(turn)) * (power) + power;
	double w = (1-fabs(power)) * (turn) + turn;
	double r = (v+w)/2;
	double l = (v-w)/2;
	Robot::drivetrain.Drive(l, r);
	Robot::arm.Move(arm_power);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystick::End() {
	Robot::drivetrain.Drive(0, 0);
}
