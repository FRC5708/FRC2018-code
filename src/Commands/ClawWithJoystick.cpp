#include "ClawWithJoystick.h"
#include "../Robot.h"

ClawWithJoystick::ClawWithJoystick()
	: frc::Command("ClawWithJoystick"){
	Requires(&Robot::claw);
}

// Called repeatedly when this Command is scheduled to run
void ClawWithJoystick::Execute() {
	switch (joyMode){
		case SINGLE_JOY: {
			if (Robot::joystick->GetRawButton(4)){
				Robot::claw.Open();
			}else if (Robot::joystick->GetRawButton(3)){
				Robot::claw.Close();
			}else{
				Robot::claw.Stop();
			}
			break;
		}
		case XBOX: {
			if (Robot::joystick->GetRawButton(4)){
				Robot::claw.Open();
			}else if (Robot::joystick->GetRawButton(3)){
				Robot::claw.Close();
			}else{
				Robot::claw.Stop();
			}
			break;
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ClawWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ClawWithJoystick::End() {

}
