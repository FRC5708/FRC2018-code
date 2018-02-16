#ifndef Wrist_H
#define Wrist_H

#include <Commands/Subsystem.h>
#include "RobotMap.h"
#include "WPILib.h"

class Wrist : public frc::Subsystem {
private:
	DoubleSolenoid* wristSolenoid = new DoubleSolenoid(WristSolenoidChannel[0],WristSolenoidChannel[1]);

public:
	Wrist();
	void InitDefaultCommand(){};
	void Open();
	void Close();
	void Stop();
};

#endif  // Wrist_H
