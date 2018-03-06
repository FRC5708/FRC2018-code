#include <Commands/ArmWithJoystick.h>
#include "../Robot.h"
#include <iostream>

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
	
	if (Robot::joyMode == SINGLE_JOY) {
		double armDir = ((Robot::joystick->GetRawButton(5) ? 1 : 0) + (Robot::joystick->GetRawButton(6) ? -1 : 0));
		
		if (Robot::joystick->GetRawButtonPressed(1)) {
			holding_arm = !holding_arm;
			std::cout << "set holding_arm to: " << holding_arm << std::endl;
		}
		if (armDir != 0) {
			Robot::arm.CancelMoveTo();

			if(fabs(arm_power) < 1){
				arm_power+=.04*armDir; //Ramup/Rampdown
			}
			Robot::arm.Move(arm_power);
		}
		else {
			arm_power = 0;
			if (holding_arm && !Robot::arm.isHolding) {
				Robot::arm.StartHold();
			}
			else if (!holding_arm) {
				Robot::arm.CancelMoveTo();
			}
		}
	}
	else {
		// right joystick button
		if(Robot::joystick->GetRawButton(10)) {
			if (!Robot::arm.isHolding) {
				Robot::arm.StartHold();
			}
		}
		else {
			Robot::arm.CancelMoveTo();
			
			// should be right joystick X
			double rawPower = Robot::joystick->GetRawAxis(4);
			
			// "dead zone" correction
			double correctedPower = (fabs(rawPower) - 0.1) * (1.0/1.1);
			if (correctedPower < 0) correctedPower = 0;
			if (rawPower < 0) correctedPower = -correctedPower;
			
			Robot::arm.Move(correctedPower);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ArmWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ArmWithJoystick::End() {

}
