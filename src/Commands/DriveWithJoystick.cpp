#include "DriveWithJoystick.h"

double currentLeftPower=0.0;
double currentRightPower=0.0;
DriveWithJoystick::DriveWithJoystick()
    : frc::Command("DriveWithJoystick"){
	Requires(&Robot::drivetrain);
}



void powerRampup(double input, double* outputVar) {
	if (fabs(input) > fabs(currentLeftPower)) {
		int sign = (input > 0) ? 1 : -1;
		*outputVar += 0.1*sign;
	}
	if (fabs(input) < fabs(*outputVar)) *outputVar = input;
}
// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
	double turn = 0;
	double power = 0;

	switch (Robot::joyMode){
		case SINGLE_JOY: {
			turn = -Robot::joystick->GetX();
			power = Robot::joystick->GetY();
			turn = inputTransform(turn, 0, 0);
			break;
		}
		case XBOX: {
			turn = Robot::joystick->GetX();
			power = Robot::joystick->GetRawAxis(3)-Robot::joystick->GetRawAxis(2);
			turn = inputTransform(turn, 0, 0.1);
			break;
		}
	}
	power = inputTransform(power, 0.2, 0.05);

	//Robot::drivetrain.DrivePolar(power, turn);
	double v = (1-fabs(turn)) * (power) + power;
	double w = (1-fabs(power)) * (turn) + turn;
	double right = (v+w)/2;
	double left = (v-w)/2;
	
	powerRampup(left, &currentLeftPower);
	powerRampup(right, &currentRightPower);
	
	Robot::drivetrain.Drive(currentLeftPower, currentRightPower);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystick::End() {
	Robot::drivetrain.Drive(0, 0);
}
