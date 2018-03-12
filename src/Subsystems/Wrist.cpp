#include "Wrist.h"
#include "../RobotMap.h"

Wrist::Wrist() : Subsystem("Wrist") {

}

void Wrist::Up(){
	wristSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
}

void Wrist::Down(){
	wristSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
}

void Wrist::Stop(){
	wristSolenoid->Set(frc::DoubleSolenoid::Value::kOff);
}
