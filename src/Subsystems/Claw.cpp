#include "Claw.h"
#include "../RobotMap.h"

Claw::Claw() : Subsystem("Claw") {

}

void Claw::Open(){
	solenoid1->Set(frc::DoubleSolenoid::Value::kForward);
	solenoid2->Set(frc::DoubleSolenoid::Value::kForward);
}

void Claw::Close(){
	solenoid1->Set(frc::DoubleSolenoid::Value::kReverse);
	solenoid2->Set(frc::DoubleSolenoid::Value::kReverse);
}

void Claw::Stop(){
	solenoid1->Set(frc::DoubleSolenoid::Value::kOff);
	solenoid2->Set(frc::DoubleSolenoid::Value::kOff);
}

void Claw::SetMove(motorMove moveType){
	currentMove=moveType;
}
