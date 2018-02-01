#include "ClawWithJoystick.h"
#include "../Robot.h"

ClawWithJoystick::ClawWithJoystick()
	: frc::Command("ClawWithJoystick"){
	Requires(&Robot::claw);
}

bool ClawWithJoystick::WasButtonJustPressed(int button) {
	bool isPressed = Robot::joystick->GetRawButton(button);

	if (isPressed) {
		if (!buttons[button - 1]) {
			buttons[button - 1] = true;
			return true;
		}
	}
	else buttons[button - 1] = false;
	return false;
}

// Called repeatedly when this Command is scheduled to run
void ClawWithJoystick::Execute() {
	switch (joyMode){
		case SINGLE_JOY: {
			if (WasButtonJustPressed(2)){
				Robot::claw.Open();
			}else if (WasButtonJustPressed(3)){
				Robot::claw.Close();
			}else{
				Robot::claw.Stop();
			}
			break;
		}
		case XBOX: {
			if (WasButtonJustPressed(2)){
				Robot::claw.Open();
			}else if (WasButtonJustPressed(3)){
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
