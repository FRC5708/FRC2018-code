#include "Arm.h"
#include <Talon.h>
#include <SmartDashboard/SmartDashboard.h>
#include "../RobotMap.h"
#include "Robot.h"



Arm::Arm(): Subsystem("Arm"),
			motor1(new frc::Talon(ArmMotorChannel1)),
		    motor2(new frc::Talon(ArmMotorChannel2)),
		    encoder(ArmEncoderChannel[0], ArmEncoderChannel[1], true),
			positionController(3, 0, 0, &encoder, this) {

	encoder.SetDistancePerPulse(1.0/360.0);
}

Arm::~Arm() {
	
}

typedef double Range[2];
// TODO: add these
constexpr Range wristUpReq[] = {};
constexpr Range wristDownReq[] = {};

void Arm::Periodic() {
	double distance = encoder.GetDistance();
	
	for (int i = 0; i != (sizeof(wristUpReq) / sizeof(*wristUpReq)); ++i) {
		if (distance > wristUpReq[i][0] && distance < wristUpReq[i][1]) {
			Robot::wrist.Open();
		}
	}
	for (int i = 0; i != (sizeof(wristDownReq) / sizeof(*wristDownReq)); ++i) {
		if (distance > wristDownReq[i][0] && distance < wristDownReq[i][1]) {
			Robot::wrist.Close();
		}
	}
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
