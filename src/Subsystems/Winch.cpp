#include "Winch.h"
#include "../RobotMap.h"
#include <Spark.h>

Winch::Winch() : Subsystem("ExampleSubsystem"),
				 leftMotor(new frc::Spark(leftWinchMotorChannel)),
				 rightMotor(new frc::Spark(rightWinchMotorChannel)), 
				 encoder(ArmEncoderChannel[0], ArmEncoderChannel[1], true),
				 positionController(1, 0.01, 0, &encoder, this, 0.02) {
	encoder.SetDistancePerPulse(1.0);
}

void Winch::SetMotors(double power) {
	power = -power;
	leftMotor->Set(power);
	rightMotor->Set(-power);
}

void Winch::MoveTo(double to) {

		positionController.SetSetpoint(to);
		positionController.Enable();
}
