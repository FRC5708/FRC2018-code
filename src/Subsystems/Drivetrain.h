#ifndef Drivetrain_H
#define Drivetrain_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include <vector>
#include "RobotMap.h"

class Drivetrain : public frc::Subsystem {
private:

	double encoderOffset;

	SpeedController *FLMotor;
	SpeedController *BLMotor;
	SpeedController *FRMotor;
	SpeedController *BRMotor;

	Encoder *FLEncoder;
	Encoder *BLEncoder;
	Encoder *FREncoder;
	Encoder *BREncoder;

	void SetMotors(double FL, double BL, double FR, double BR);
	void StopMotors();

public:
	Drivetrain();
	void InitDefaultCommand();
	void Drive(double left, double right);			//Drives left and right wheels accordingly

};

#endif  // Drivetrain_H
