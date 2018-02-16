#include <Commands/ArmWithJoystick.h>
#include "../Robot.h"

ArmWithJoystick::ArmWithJoystick()
	: frc::Command("ClawWithJoystick"){
	Requires(&Robot::claw);
}

// Called repeatedly when this Command is scheduled to run
void ArmWithJoystick::Execute() {
	switch (Robot::joyMode){
		case SINGLE_JOY: {
			if (Robot::joystick->GetRawButton(4)){
				Robot::claw.Open();
			}else if (Robot::joystick->GetRawButton(3)){
				Robot::claw.Close();
			}else if (Robot::joystick->GetRawButton(8)){
				Robot::hookRelease.realeaseHookArm();
			}else{
				Robot::claw.Stop();
			}
			break;
		}
		case XBOX: {
			break;
		}
	}
	if (Robot::joystick->GetRawButton(4)){
		Robot::claw.Open();
	}else if (Robot::joystick->GetRawButton(3)){
		Robot::claw.Close();
	}else{
		Robot::claw.Stop();
	}
	if(Robot::joystick->GetRawButtonPressed(7)){
		switch (wrist_is_up){
		case 1:
			wrist_is_up = 0;
			Robot::wrist.Open();
			break;
		case 0:
			wrist_is_up=1;
			Robot::wrist.Close();
			break;
		}
	}
	double arm_power = ((Robot::joystick->GetRawButton(5) ? 1 : 0) + (Robot::joystick->GetRawButton(6) ? -1 : 0));
	Robot::arm.Move(arm_power);
}

// Make this return true when this Command no longer needs to run execute()
bool ArmWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ArmWithJoystick::End() {

}
