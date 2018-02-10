#include "TurnAngle.h"
#include <iostream>

TurnAngle::TurnAngle(double angle) {
	Requires(&Robot::drivetrain);
	
	//angle = angle - (trunc(angle / 360) * 360);
	//source.gyroCorrection = -(trunc(Robot::gyro->GetAngle() / 360) * 360);
	
	
	pid.SetAbsoluteTolerance(1); // degrees
	pid.SetSetpoint(angle);
	
}

// Called just before this Command runs the first time
void TurnAngle::Initialize() {
	std::cout << "turning to angle: " << pid.GetSetpoint() << std::endl;
	
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
	std::cout << "ended turn" << std::endl;
	pid.Disable();
	Robot::drivetrain.Drive(0,0);
}

double TurnAngle::TurnAnglePIDSource::PIDGet() {
	return Robot::gyro->GetAngle() + gyroCorrection;
}

void TurnAngle::TurnAnglePIDOutput::PIDWrite(double d) {
	//if (fabs(d) < 0.2) d = (d > 0 ? 0.2 : -0.2);
	SmartDashboard::PutNumber("turning power", d);
	Robot::drivetrain.Drive(-d, d);
}
