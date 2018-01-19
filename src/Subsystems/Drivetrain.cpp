#include "Drivetrain.h"
#include "../RobotMap.h"
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

double Drivetrain::Limit(double number) {
  if (number > 1.0) {
    return 1.0;
  }
  if (number < -1.0) {
    return -1.0;
  }
  return number;
}

void Drivetrain::Drive(double left, double right)
	leftControl.SetSetpoint(11*left);
	rightControl.SetSetpoint(11*right);
}

void Drivetrain::DrivePolar(double moveValue, double rotateValue) {

  double leftMotorOutput;
  double rightMotorOutput;

  moveValue = Limit(moveValue);
  rotateValue = Limit(rotateValue);


  if (moveValue > 0.0) {
    if (rotateValue > 0.0) {
      leftMotorOutput = moveValue - rotateValue;
      rightMotorOutput = std::max(moveValue, rotateValue);
    } else {
      leftMotorOutput = std::max(moveValue, -rotateValue);
      rightMotorOutput = moveValue + rotateValue;
    }
  } else {
    if (rotateValue > 0.0) {
      leftMotorOutput = -std::max(-moveValue, rotateValue);
      rightMotorOutput = moveValue + rotateValue;
    } else {
      leftMotorOutput = moveValue - rotateValue;
      rightMotorOutput = -std::max(-moveValue, -rotateValue);
    }
  }
  Drive(leftMotorOutput,rightMotorOutput);
}

void Drivetrain::ResetDistance(){
	LeftEncoder->Reset();
	RightEncoder->Reset();
}

double Drivetrain::GetDistance(){
	return ((LeftEncoder->Get()+RightEncoder->Get())/2)*WheelCircumference;
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




