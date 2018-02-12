
#include <Subsystems/Arm.h>
#include <Talon.h>
#include "../RobotMap.h"



Arm::Arm(): Subsystem("Arm"),
			motor1(new frc::Talon(ArmMotorChannel1)),
		    motor2(new frc::Talon(ArmMotorChannel2)),
			armRelease(new frc::Servo(ArmReleaseChannel)),
		    encoder(ArmEncoderChannel[0], ArmEncoderChannel[1]) {

	encoder.SetDistancePerPulse(1.0/360.0);
}
void Arm::Move(double power) {
	motor1->Set(power);
	motor2->Set(power);
}

void Arm::SetReleasePosition(double position){
	armRelease->Set(position);
}

Arm::~Arm() {
	// TODO Auto-generated destructor stub
}

