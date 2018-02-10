#ifndef Drivetrain_H
#define Drivetrain_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include <vector>
#include "RobotMap.h"
#include <cmath>



class Drivetrain : public frc::Subsystem {
public:
	Drivetrain();
	void InitDefaultCommand() {};
	double Limit(double number);
	void Drive(double left, double right);				//Drives left and right wheels accordingly
	void DrivePolar(double moveValue, double rotateValue);	//Drives at moveValue and rotateValue
	void ResetDistance();
	double GetDistance();

	Encoder* leftEncoder = new frc::Encoder(LeftEncoderChannel[0],LeftEncoderChannel[1], false);
	Encoder* rightEncoder = new frc::Encoder(RightEncoderChannel[0],RightEncoderChannel[1], true);
private:

	SpeedController* FLMotor = new frc::Spark(FLMotorChannel);
	SpeedController* BLMotor = new frc::Spark(BLMotorChannel);
	SpeedController* FRMotor = new frc::Spark(FRMotorChannel);
	SpeedController* BRMotor = new frc::Spark(BRMotorChannel);
};



#endif  // Drivetrain_H
