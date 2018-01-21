#include "Drivetrain.h"
#include "../Robot.h"
#include <SmartDashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <iostream>
#include <math.h>

void initPIDController(PIDController* controller) {
	controller->SetOutputRange(-0.2, 0.2);
	controller->SetInputRange(-20, 20);
	
	controller->Enable();
}

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain"), 
leftSource(leftEncoder), 
rightSource(rightEncoder),
leftOutput(FLMotor, BLMotor),
rightOutput(FRMotor, BRMotor) {
	
	encoderOffset = 0.0;
	
	initPIDController(&rightControl);
	initPIDController(&leftControl);
	
	leftEncoder->SetDistancePerPulse(1.0/360.0);
	rightEncoder->SetDistancePerPulse(1.0/360.0);

	FLMotor->SetInverted(true);
	BLMotor->SetInverted(true);
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
	double leftRate = leftEncoder->GetRate();
	double rightRate = leftEncoder->GetRate();
	//double meanRate = (leftRate + rightRate) / 2;
	
	double nancheck = left/right + right/left;
	if (!std::isnan(nancheck) && std::isfinite(nancheck)) {
	
		leftControl.SetSetpoint((left/right * leftRate + rightRate) / (left/right + 1));
		rightControl.SetSetpoint((right/left * rightRate + leftRate) / (right/left + 1));
	}
	else {
		// we're turning
		leftControl.SetSetpoint(leftRate);
		rightControl.SetSetpoint(rightRate);
	}

	leftOutput.basePower = left;
	rightOutput.basePower = right;
	
	/*FLMotor->Set(left);
	BLMotor->Set(left);
	FRMotor->Set(right);
	BRMotor->Set(right);*/
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
	//NetworkTable::GetTable("datatable")->PutNumber("encoder", toReturn);
	//NetworkTable::GetTable("datatable")->PutNumber("encoder", distance);


	if (abs(toReturn > abs(maxEncoderRate))) maxEncoderRate = toReturn;
	if (abs(distance > abs(maxEncoderDistance))) maxEncoderDistance = distance;

	std::cout << "encoder: rate: " << toReturn << 
			", distance: " << distance <<
			", max rate: " << maxEncoderRate << 
			", max distance " << maxEncoderDistance 
			<< std::endl;
	return toReturn;
}


void Drivetrain::DoubleMotorPIDOutput::PIDWrite(double correction) {
	double power;
	if (basePower > 0.05) power = basePower + correction;
	else power = 0;
	
	motor1->Set(power);
	motor2->Set(power);
}





