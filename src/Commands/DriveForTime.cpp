#include "DriveForTime.h"

DriveForTime::DriveForTime(int _t) {
	Requires(&Robot::drivetrain);
	time = _t;
	count = 0;
}

// Called just before this Command runs the first time
void DriveForTime::Initialize() {
	Robot::drivetrain.Drive(-0.75,-0.75);
}

// Called repeatedly when this Command is scheduled to run
void DriveForTime::Execute() {
	count++;
}

// Make this return true when this Command no longer needs to run execute()
bool DriveForTime::IsFinished() {
	return (count > time);
}

// Called once after isFinished returns true
void DriveForTime::End() {
	Robot::drivetrain.Drive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForTime::Interrupted() {

}
