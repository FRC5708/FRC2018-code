#ifndef Claw_H
#define Claw_H

#include <Commands/Subsystem.h>
#include "RobotMap.h"
#include "WPILib.h"
#include <Spark.h>

enum motorMove {FORWARD, STOP, NONE, REVERSE};

class Claw : public frc::Subsystem {
private:
	DoubleSolenoid* solenoid1 = new DoubleSolenoid(ClawSolenoid1Channel[0],ClawSolenoid1Channel[1]);
	DoubleSolenoid* solenoid2 = new DoubleSolenoid(ClawSolenoid2Channel[0],ClawSolenoid2Channel[1]);
	
	SpeedController* motor1 = new Spark(intakeMotorChannel1);
	SpeedController* motor2 = new Spark(intakeMotorChannel2);

public:
	motorMove currentMove = NONE;
	Claw();
	void InitDefaultCommand(){};
	void Open();
	void Close();
	void Stop();
	void MoveMotors(double power) { motor1->Set(power); motor2->Set(-power); }
	void SetMove(motorMove);
};

#endif  // Claw_H
