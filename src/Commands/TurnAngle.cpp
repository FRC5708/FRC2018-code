#include "TurnAngle.h"

TurnAngle::TurnAngle(double angle) {
	Requires(&Robot::drivetrain);
	pid.SetAbsoluteTolerance(1); // one degree
	pid.SetSetpoint(angle);
}

// Called just before this Command runs the first time
void TurnAngle::Initialize() {
	//Robot::gyro->Reset();
	pid.Reset();
	pid.Enable();
	pid.SetOutputRange(-0.5, 0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool TurnAngle::IsFinished() {
	return pid.OnTarget();
}

// Called once after isFinished returns true
void TurnAngle::End() {
	pid.Disable();
	Robot::drivetrain.Drive(0,0);
}

double TurnAngle::TurnAnglePIDSource::PIDGet() {
	return Robot::gyro->GetAngle();
}

void TurnAngle::TurnAnglePIDOutput::PIDWrite(double d) {
	Robot::drivetrain.Drive(d, -d);
}
