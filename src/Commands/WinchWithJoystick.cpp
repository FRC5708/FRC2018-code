#include "WinchWithJoystick.h"
#include "../Robot.h"

WinchWithJoystick::WinchWithJoystick() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::winch);
}

// Called repeatedly when this Command is scheduled to run
void WinchWithJoystick::Execute() {
	switch (Robot::joyMode){
			case SINGLE_JOY: {
				if (Robot::joystick->GetRawButton(9)){
					Robot::winch.setMotors(0.5);
				}else{
					Robot::winch.setMotors(0);
				}
				break;
			}
			case XBOX: {
				if (Robot::joystick->GetRawButton(9)){
					Robot::winch.setMotors(0.5);
				}else{
					Robot::winch.setMotors(0);
				}
				break;
			}
		}
}

// Make this return true when this Command no longer needs to run execute()
bool WinchWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void WinchWithJoystick::End() {

}
