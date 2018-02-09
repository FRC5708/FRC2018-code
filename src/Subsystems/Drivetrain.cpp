#include "Drivetrain.h"
#include "../Robot.h"
#include <SmartDashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <iostream>
#include <math.h>


Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain") {
	
	leftEncoder->SetDistancePerPulse(1.0/360.0);
	rightEncoder->SetDistancePerPulse(1.0/360.0);
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

void Drivetrain::Drive(double left, double right) {
	FLMotor->Set(left);
	BLMotor->Set(left);
	FRMotor->Set(-right);
	BRMotor->Set(-right);
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
	leftEncoder->Reset();
	rightEncoder->Reset();

	leftEncoder->SetDistancePerPulse(1.0/360.0);
	rightEncoder->SetDistancePerPulse(1.0/360.0);
}

double Drivetrain::GetDistance() {
	return ((leftEncoder->GetDistance()+rightEncoder->GetDistance())/2.0)*WheelCircumference;
}




