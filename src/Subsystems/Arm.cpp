#include "Arm.h"
#include <Talon.h>
#include "../RobotMap.h"



Arm::Arm(): Subsystem("Arm"),
			motor1(new frc::Talon(ArmMotorChannel1)),
		    motor2(new frc::Talon(ArmMotorChannel2)),
		    encoder(ArmEncoderChannel[0], ArmEncoderChannel[1]),
			positionController(4, 0.01, 0, &encoder, this) {

	encoder.SetDistancePerPulse(1.0/360.0);
	
}

Arm::~Arm() {
	// TODO Auto-generated destructor stub
}

void Arm::MoveTo(double to) {
	positionController.SetSetpoint(to);
	positionController.Enable();
}

void Arm::Move(double power) {
	motor1->Set(power);
	motor2->Set(power);
}
