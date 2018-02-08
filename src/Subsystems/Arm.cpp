
#include <Subsystems/Arm.h>
#include <Victor.h>
#include "../RobotMap.h"

Arm::Arm(): motor1(new frc::Victor(ArmMotorChannel1)), 
		    motor2(new frc::Victor(ArmMotorChannel2)),
		    encoder(ArmEncoderChannel[0], ArmEncoderChannel[1]) {

	encoder.SetDistancePerPulse(1.0/1440.0);
}
void Arm::Move(double power) {
	motor1->Set(power);
	motor2->Set(power);
}

Arm::~Arm() {
	// TODO Auto-generated destructor stub
}

