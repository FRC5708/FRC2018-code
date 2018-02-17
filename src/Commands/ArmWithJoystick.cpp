#include <Commands/ArmWithJoystick.h>
#include "../Robot.h"

ArmWithJoystick::ArmWithJoystick()
	: frc::Command("ClawWithJoystick"){
	Requires(&Robot::claw);
}

// Called repeatedly when this Command is scheduled to run
void ArmWithJoystick::Execute() {
	
	if (Robot::joystick->GetRawButton(5)) {
		Robot::hookRelease.realeaseHookArm();
	}
	if (Robot::joystick->GetRawButtonPressed(3)) {
		if (claw_is_open) {
			Robot::claw.Close();
			claw_is_open = false;
		}
		else {
			Robot::claw.Open();
			claw_is_open = true;
		}
	}
	if (Robot::joystick->GetRawButtonPressed(4)) {
		if (wrist_is_up) {
			Robot::wrist.Close();
			wrist_is_up = false;
		}
		else {
			Robot::wrist.Open();
			wrist_is_up = true;
		}
	}
	double arm_power = ((Robot::joystick->GetRawButton(5) ? 1 : 0) + (Robot::joystick->GetRawButton(6) ? -1 : 0));
	
	if (arm_power != 0) {
		Robot::arm.Move(arm_power);
	}
	else if (!Robot::arm.isHolding) {
		Robot::arm.Hold(); 
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ArmWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ArmWithJoystick::End() {

}
