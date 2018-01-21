#include "Drivetrain.h"
#include "../Robot.h"
#include <SmartDashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <iostream>
#include <math.h>

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain"), 
leftSource(leftEncoder), 
rightSource(rightEncoder),
leftOutput(FLMotor, BLMotor),
rightOutput(FRMotor, BRMotor) {
	
	encoderOffset = 0.0;
	leftControl.Enable();
	rightControl.Enable();
	
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

void Drivetrain::Drive(double left, double right){
	//leftControl.SetSetpoint(left);
	//rightControl.SetSetpoint(right);

	FLMotor->Set(left);
	BLMotor->Set(left);
	FRMotor->Set(right);
	BRMotor->Set(right);
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
}

double Drivetrain::GetDistance(){
	return ((leftEncoder->Get()+rightEncoder->Get())/2)*WheelCircumference;
}

double maxEncoderDistance = 0;
double maxEncoderRate = 0;

double Drivetrain::RatePIDSource::PIDGet() {
	double toReturn = encoder->GetRate();
	double distance = encoder->GetDistance();
	//SmartDashboard::PutNumber("Encoder", toReturn);
	NetworkTable::GetTable("datatable")->PutNumber("encoder", toReturn);
	NetworkTable::GetTable("datatable")->PutNumber("encoder", distance);


	if (abs(toReturn > abs(maxEncoderRate))) maxEncoderRate = toReturn;
	if (abs(distance > abs(maxEncoderDistance))) maxEncoderDistance = distance;

	std::cout << "encoder: rate: " << toReturn << ", distance: " << distance << ", max rate: " << maxEncoderRate << ", max distance" << maxEncoderDistance << std::endl;
	return toReturn;
}


void Drivetrain::DoubleMotorPIDOutput::PIDWrite(double d) {
	//motor1->Set(d);
	//motor2->Set(d);
}





