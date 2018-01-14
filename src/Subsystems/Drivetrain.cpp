#include "Drivetrain.h"
#include "../RobotMap.h"

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain") {

	encoderOffset = 0;

	FLMotor = new frc::Victor(FLMotorChannel);
	BLMotor = new frc::Victor(BLMotorChannel);
	FRMotor = new frc::Victor(FRMotorChannel);
	BRMotor = new frc::Victor(BRMotorChannel);

	FLEncoder = new frc::Encoder(FLEncoderChannel[0],FLEncoderChannel[1]);
	BLEncoder = new frc::Encoder(BLEncoderChannel[0],BLEncoderChannel[1]);
	FREncoder = new frc::Encoder(FREncoderChannel[0],FREncoderChannel[1]);
	BREncoder = new frc::Encoder(BREncoderChannel[0],BREncoderChannel[1]);
}

void Drivetrain::SetMotors(double FL, double BL, double FR, double BR){
	FLMotor->Set(FL);
	BLMotor->Set(BL);
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
	SetMotors(left,left,right,right);
}
