#include "Drivetrain.h"
#include "../Robot.h"

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain") {
	encoderOffset = 0;
	leftControl.Enable();
	rightControl.Enable();
}

void Drivetrain::SetMotors(double FL, double BL, double FR, double BR){
	FLMotor->Set(-FL);
	BLMotor->Set(-BL);
	FRMotor->Set(FR);
	BRMotor->Set(BR);
}

void Drivetrain::StopMotors(){
	FLMotor->Set(0);
	BLMotor->Set(0);
	FRMotor->Set(0);
	BRMotor->Set(0);
}

void Drivetrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Drivetrain::Drive(double left, double right){
	leftControl.SetSetpoint(11*left);
	rightControl.SetSetpoint(11*right);
}

double Drivetrain::LeftSidePIDSource::PIDGet() {
	return Robot::drivetrain.leftEncoder->GetRate();
}

double Drivetrain::RightSidePIDSource::PIDGet() {
	return Robot::drivetrain.rightEncoder->GetRate();
}

void Drivetrain::LeftSidePIDOutput::PIDWrite(double d) {
	Robot::drivetrain.FLMotor->Set(d);
	Robot::drivetrain.BLMotor->Set(d);
}

void Drivetrain::RightSidePIDOutput::PIDWrite(double d) {
	Robot::drivetrain.FRMotor->Set(d);
	Robot::drivetrain.BRMotor->Set(d);
}



