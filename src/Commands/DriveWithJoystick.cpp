#include "DriveWithJoystick.h"


DriveWithJoystick::DriveWithJoystick()
    : frc::Command("DriveWithJoystick"){
	Requires(&Robot::drivetrain);
}

// from 0 to inputChangePosition in joystick, power output is 0 to outputChangePosition. This makes the robot easier to control at low speeds.
double powerTransform(double input, double minPowerOutput, double inputDeadZone) {
	constexpr double inputChangePosition = 0.75;
	constexpr double outputChangePosition = 0.5;

	double output = 0;
	if (fabs(input) <= inputDeadZone) {
		output = 0;
	}
	else if (fabs(input) <= inputChangePosition) {
		output = (fabs(input) / inputChangePosition * (outputChangePosition - minPowerOutput)) + minPowerOutput;
	}
	else {
		output = (fabs(input) - inputChangePosition)
				/ (1 - inputChangePosition)
				* (1 - outputChangePosition)
				+ outputChangePosition;
	}
	if (input < 0) output = -output;
	return output;
} 

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
	double turn = 0;
	double power = 0;

	switch (Robot::joyMode){
		case SINGLE_JOY: {
			turn = -Robot::joystick->GetX();
			power = Robot::joystick->GetY();
			turn = powerTransform(turn, 0, 0);
			break;
		}
		case XBOX: {
			turn = Robot::joystick->GetX();
			power = Robot::joystick->GetRawAxis(3)-Robot::joystick->GetRawAxis(2);
			turn = powerTransform(turn, 0, 0.1);
			break;
		}
	}
	power = powerTransform(power, 0.2, 0.05);

	//Robot::drivetrain.DrivePolar(power, turn);
	double v = (1-fabs(turn)) * (power) + power;
	double w = (1-fabs(power)) * (turn) + turn;
	double r = (v+w)/2;
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
