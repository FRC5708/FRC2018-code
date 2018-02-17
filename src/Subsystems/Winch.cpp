#include "Winch.h"
#include "../RobotMap.h"

Winch::Winch() : Subsystem("ExampleSubsystem"),
				 leftMotor(new frc::Spark(leftWinchMotorChannel)),
				 rightMotor(new frc::Spark(rightWinchMotorChannel)){
}

void Winch::setMotors(double power){
	leftMotor->Set(power);
	rightMotor->Set(-power);
}
