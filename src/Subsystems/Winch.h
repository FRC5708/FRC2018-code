#ifndef Winch_H
#define Winch_H

#include <Commands/Subsystem.h>
#include "WPILib.h"

class Winch : public frc::Subsystem {
public:
	Winch();
	void setMotors(double power);
	frc::Spark* leftMotor;
	frc::Spark* rightMotor;
};

#endif  // Winch_H
