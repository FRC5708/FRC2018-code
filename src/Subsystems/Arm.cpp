#include "Arm.h"
#include <Talon.h>
#include <SmartDashboard/SmartDashboard.h>
#include "../RobotMap.h"



Arm::Arm(): Subsystem("Arm"),
			motor1(new frc::Talon(ArmMotorChannel1)),
		    motor2(new frc::Talon(ArmMotorChannel2)),
		    encoder(ArmEncoderChannel[0], ArmEncoderChannel[1], true),
			positionController(3, 0, 0, &encoder, this) {

	encoder.SetDistancePerPulse(1.0/360.0);
	
}

Arm::~Arm() {
	// TODO Auto-generated destructor stub
}

void Arm::MoveTo(double to) {
	// disables method if encoder is backwards
	if (encoder.GetDistance() > -0.1) {

		positionController.SetSetpoint(to);
		positionController.Enable();
	}
}

void Arm::Move(double power) {
	motor1->Set(power);
	motor2->Set(power);

	SmartDashboard::PutNumber("Arm power", power);
}
