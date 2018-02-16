#include "Wrist.h"
#include "../RobotMap.h"

Wrist::Wrist() : Subsystem("Wrist") {

}

void Wrist::Open(){
	wristSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
}

void Wrist::Close(){
	wristSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
}

void Wrist::Stop(){
	wristSolenoid->Set(frc::DoubleSolenoid::Value::kOff);
}
