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
	
	
	if (Robot::joystick->GetRawButton(WINCH_RUN)) {
		Robot::winch.setMotors(1);
	} else {
		Robot::winch.setMotors(0);
	}


}

// Make this return true when this Command no longer needs to run execute()
bool WinchWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void WinchWithJoystick::End() {

}
