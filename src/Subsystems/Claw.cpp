#include "Claw.h"
#include "../RobotMap.h"

Claw::Claw() : Subsystem("ExampleSubsystem") {

}

void Claw::Open(){
	clawSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
}

void Claw::Close(){
	clawSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
}

void Claw::Stop(){
	clawSolenoid->Set(frc::DoubleSolenoid::Value::kOff);
}
