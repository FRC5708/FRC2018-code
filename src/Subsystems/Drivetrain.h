#ifndef Drivetrain_H
#define Drivetrain_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include <vector>

class Drivetrain : public frc::Subsystem {
private:

	double encoderOffset;
	double wheelCircumference;

	int FLMotorChannel;
	int BLMotorChannel;
	int FRMotorChannel;
    int BRMotorChannel;

    int FLEncoderChannel[2] = {0};
    int BLEncoderChannel[2] = {0};
    int FREncoderChannel[2] = {0};
    int BREncoderChannel[2] = {0};

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
