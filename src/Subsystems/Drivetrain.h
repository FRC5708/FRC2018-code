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

	
private:

	SpeedController* FLMotor = new frc::Victor(FLMotorChannel);
	SpeedController* BLMotor = new frc::Victor(BLMotorChannel);
	SpeedController* FRMotor = new frc::Victor(FRMotorChannel);
	SpeedController* BRMotor = new frc::Victor(BRMotorChannel);

	Encoder* leftEncoder = new frc::Encoder(LeftEncoderChannel[0],LeftEncoderChannel[1], false);
	Encoder* rightEncoder = new frc::Encoder(RightEncoderChannel[0],RightEncoderChannel[1], true);
};



#endif  // Drivetrain_H
