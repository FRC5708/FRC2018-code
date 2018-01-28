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

	class RatePIDSource : public frc::PIDSource {
	public:
		virtual ~RatePIDSource() = default;
		double PIDGet() override;
		Encoder* encoder;
		RatePIDSource(Encoder* encoder): encoder(encoder) {}; 
	};

	class DoubleMotorPIDOutput : public frc::PIDOutput {
	public:
		virtual ~DoubleMotorPIDOutput() = default;
		void PIDWrite(double d) override;
		SpeedController* motor1;
		SpeedController* motor2;
		double basePower;
		DoubleMotorPIDOutput(SpeedController* motor1, SpeedController* motor2): motor1(motor1), motor2(motor2) {};
	};

private:

	double encoderOffset;

	SpeedController* FLMotor = new frc::Victor(FLMotorChannel);
	SpeedController* BLMotor = new frc::Victor(BLMotorChannel);
	SpeedController* FRMotor = new frc::Victor(FRMotorChannel);
	SpeedController* BRMotor = new frc::Victor(BRMotorChannel);

	Encoder* leftEncoder= new frc::Encoder(LeftEncoderChannel[0],LeftEncoderChannel[1]);
	Encoder* rightEncoder = new frc::Encoder(RightEncoderChannel[0],RightEncoderChannel[1]);

	RatePIDSource leftSource;
	DoubleMotorPIDOutput leftOutput;
	frc::PIDController leftControl{0.01, 0, 0, leftSource, leftOutput};

	RatePIDSource rightSource;
	DoubleMotorPIDOutput rightOutput;
	frc::PIDController rightControl{0.01, 0, 0, rightSource, rightOutput};

};



#endif  // Drivetrain_H
