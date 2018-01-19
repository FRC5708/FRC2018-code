 #include "Drivetrain.h"
#include "../RobotMap.h"

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain") {

	encoderOffset = 0;
	LeftControl = new frc::PIDController(0.1, 0.001, 0, LeftEncoder, &LeftMotors);
	RightControl = new frc::PIDController(0.1, 0.001, 0, RightEncoder, &RightMotors);
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

void Drivetrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Drivetrain::Drive(double left, double right){
	LeftMotors.outputMultiplier = left;
	RightMotors.outputMultiplier = right;
	
	double leftRate = LeftEncoder->GetRate();
	double rightRate = RightEncoder->GetRate();
	double meanRate = (leftRate + rightRate)/2;
	
	LeftControl->SetSetpoint(meanRate * (left/right));
	RightControl->SetSetpoint(meanRate * (right/left));
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

}

double Drivetrain::GetDistance(){

}

void DoubleMotor::PIDWrite(double output) {
	motor1->Set(output*outputMultiplier);
	motor2->Set(output*outputMultiplier);
}




