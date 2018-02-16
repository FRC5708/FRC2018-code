#include "ReleaseHook.h"

ReleaseHook::ReleaseHook() {
	Requires(&Robot::arm);
}

// Called repeatedly when this Command is scheduled to run
void ReleaseHook::Execute() {
	Robot::arm.SetReleasePosition(1);
}

// Make this return true when this Command no longer needs to run execute()
bool ReleaseHook::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ReleaseHook::End() {

}
