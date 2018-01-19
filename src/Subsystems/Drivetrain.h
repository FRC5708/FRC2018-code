#ifndef Drivetrain_H
#define Drivetrain_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include <vector>
#include "RobotMap.h"
#include <cmath>



struct DoubleMotor : PIDOutput {
	virtual ~DoubleMotor() {};
	SpeedController* motor1;
	SpeedController* motor2;
	
	double outputMultiplier = 0;
	
	
	void PIDWrite(double output) override;
	DoubleMotor(SpeedController* motor1, SpeedController* motor2): motor1(motor1), motor2(motor2) {};
};

class Drivetrain : public frc::Subsystem {
private:

	double encoderOffset;

	SpeedController* FLMotor = new frc::Victor(FLMotorChannel);
	SpeedController* BLMotor = new frc::Victor(BLMotorChannel);
	SpeedController* FRMotor = new frc::Victor(FRMotorChannel);
	SpeedController* BRMotor = new frc::Victor(BRMotorChannel);
	
	DoubleMotor LeftMotors = DoubleMotor(FLMotor, BLMotor);
	DoubleMotor RightMotors = DoubleMotor(FRMotor, BRMotor);

	Encoder *LeftEncoder= new frc::Encoder(LeftEncoderChannel[0],LeftEncoderChannel[1]);
	Encoder *RightEncoder = new frc::Encoder(RightEncoderChannel[0],RightEncoderChannel[1]);
	
	PIDController* LeftControl;
	PIDController* RightControl;

	void SetMotors(double FL, double BL, double FR, double BR);
	void StopMotors();

public:
	Drivetrain();
	void InitDefaultCommand();
	double Limit(double number);
	void Drive(double left, double right);				//Drives left and right wheels accordingly
	void DrivePolar(double moveValue, double rotateValue);	//Drives at moveValue and rotateValue
	void ResetDistance();
	double GetDistance();
};



#endif  // Drivetrain_H
