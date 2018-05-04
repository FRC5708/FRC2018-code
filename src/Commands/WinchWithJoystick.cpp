#include "WinchWithJoystick.h"
#include "../Robot.h"
#include <ControlMap.h>

WinchWithJoystick::WinchWithJoystick() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::winch);
}

// Called repeatedly when this Command is scheduled to run
void WinchWithJoystick::Execute() {
	if (Robot::joyMode == JoystickMode::SINGLE_JOY) {

		if (Robot::joystick->GetRawButton(JOY_WINCH_UP)) {
			Robot::winch.SetMotors(.1);
		} 
		else if (Robot::joystick->GetRawButton(JOY_WINCH_DOWN)) {
			Robot::winch.SetMotors(-.1);
		}
		else {
			Robot::winch.SetMotors(0);
		}
	}
	else {
		double power = inputTransform(Robot::joystick->GetRawAxis(XBOX_WINCH_AXIS), 0.1, 0.05, 0, 0);
		if (power > 0) power *= 0.8; //So that we don't break things!
		else power *= 0.55;
		if (Robot::joystick->GetRawButton(WINCH_HOLD)) {
			if (!Robot::winch.isHolding) Robot::winch.StartHold();	
		}
		else {
			Robot::winch.CancelMoveTo();
		}
		
		if (!Robot::winch.isHolding) Robot::winch.SetMotors(power);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool WinchWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void WinchWithJoystick::End() {

}
