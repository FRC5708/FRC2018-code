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
	void InitDefaultCommand();
	void Drive(double left, double right);			//Drives left and right wheels accordingly

	class LeftSidePIDSource : public frc::PIDSource {
	public:
		virtual ~LeftSidePIDSource() = default;
		double PIDGet() override;
	};

	class LeftSidePIDOutput : public frc::PIDOutput {
	public:
		virtual ~LeftSidePIDOutput() = default;
		void PIDWrite(double d) override;
	};

	class RightSidePIDSource : public frc::PIDSource {
	public:
		virtual ~RightSidePIDSource() = default;
		double PIDGet() override;
	};

	class RightSidePIDOutput : public frc::PIDOutput {
	public:
		virtual ~RightSidePIDOutput() = default;
		void PIDWrite(double d) override;
	};
private:

	double encoderOffset;

	SpeedController* FLMotor = new frc::Victor(FLMotorChannel);
	SpeedController* BLMotor = new frc::Victor(BLMotorChannel);
	SpeedController* FRMotor = new frc::Victor(FRMotorChannel);
	SpeedController* BRMotor = new frc::Victor(BRMotorChannel);

	Encoder* leftEncoder= new frc::Encoder(LeftEncoderChannel[0],LeftEncoderChannel[1]);
	Encoder* rightEncoder = new frc::Encoder(RightEncoderChannel[0],RightEncoderChannel[1]);

	LeftSidePIDSource leftSource;
	LeftSidePIDOutput leftOutput;
	frc::PIDController leftControl{4, 0, 0, leftSource, leftOutput};

	RightSidePIDSource rightSource;
	RightSidePIDOutput rightOutput;
	frc::PIDController rightControl{4, 0, 0, rightSource, rightOutput};

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
