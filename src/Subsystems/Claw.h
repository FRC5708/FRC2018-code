#ifndef Claw_H
#define Claw_H

#include <Commands/Subsystem.h>
#include "RobotMap.h"
#include "WPILib.h"

class Claw : public frc::Subsystem {
private:
	DoubleSolenoid* clawSolenoid = new DoubleSolenoid(ClawSolenoidChannel[0],ClawSolenoidChannel[1]);

public:
	Claw();
	void InitDefaultCommand(){};
	void Open();
	void Close();
	void Stop();
};

#endif  // Claw_H
