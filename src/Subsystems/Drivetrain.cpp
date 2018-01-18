  #include "Drivetrain.h"
#include "../RobotMap.h"

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain") {

	encoderOffset = 0;
	LeftControl = new PIDController(0.1, 0.001, 0, LeftEncoder, &LeftMotors);
	RightControl = new PIDController(0.1, 0.001, 0, RightEncoder, &RightMotors);
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
	LeftMotors.outputMultiplier = left;
	RightMotors.outputMultiplier = right;
	
	double leftRate = LeftEncoder->GetRate();
	double rightRate = RightEncoder->GetRate();
	double meanRate = (leftRate + rightRate)/2;
	
	LeftControl->SetSetpoint(meanRate * (left/right));
	RightControl->SetSetpoint(meanRate * (right/left));
}

void DoubleMotor::PIDWrite(double output) {
	motor1->Set(output*outputMultiplier);
	motor2->Set(output*outputMultiplier);
}



