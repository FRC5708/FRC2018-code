#include "Arm.h"
#include <Talon.h>
#include <SmartDashboard/SmartDashboard.h>
#include "../RobotMap.h"



Arm::Arm(): Subsystem("Arm"),
			motor1(new frc::Talon(ArmMotorChannel1)),
		    motor2(new frc::Talon(ArmMotorChannel2)),
		    encoder(ArmEncoderChannel[0], ArmEncoderChannel[1], true),
			positionController(3, 0.01, 0, &encoder, this) {

	encoder.SetDistancePerPulse(1.0/360.0);
}

Arm::~Arm() {
	
}

<<<<<<< HEAD
// lowering start: 12 in above resting point

constexpr double gentleLoweringStart = Arm::CHAIN_RATIO*12/(Arm::LENGTH*2*M_PI);
=======
// arm length: 40 in
// lowering start: 12 in above starting point
// chain ratio: 1:4
/*
constexpr double gentleLoweringStart = 4*12/(40*2*M_PI);
>>>>>>> e52f129918d1231ae8691896f1030003a9a3b778
constexpr double gentleLoweringRate = -0.1;
constexpr double loweringPowerMult = 0.5;
*/
void Arm::Periodic() {
	/*
	// TODO: make sure Encoder::GetRate returns a signed value
	double rate = encoder.GetRate();
	if (encoder.GetDistance() < gentleLoweringStart && rate < gentleLoweringRate) {
		
		minPower = loweringPowerMult * -(rate - gentleLoweringRate);
	}
	else minPower = -1;
	*/
}

void Arm::MoveTo(double to) {
	// disables method if encoder is backwards
	if (encoder.GetDistance() > -0.1) {

		positionController.SetSetpoint(to);
		positionController.Enable();
	}
}

void Arm::Move(double power) {
	//power = std::max(power, minPower);
	motor1->Set(power);
	motor2->Set(power);

	SmartDashboard::PutNumber("Arm power", power);
}
