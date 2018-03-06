#ifndef Claw_H
#define Claw_H

#include <Commands/Subsystem.h>
#include "RobotMap.h"
#include "WPILib.h"

class Claw : public frc::Subsystem {
private:
	DoubleSolenoid* solenoid1 = new DoubleSolenoid(ClawSolenoid1Channel[0],ClawSolenoid1Channel[1]);
	DoubleSolenoid* solenoid2 = new DoubleSolenoid(ClawSolenoid2Channel[0],ClawSolenoid2Channel[1]);

public:
	Claw();
	void InitDefaultCommand(){};
	void Open();
	void Close();
	void Stop();
};

#endif  // Claw_H
