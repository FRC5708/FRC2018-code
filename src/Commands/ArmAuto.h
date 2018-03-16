#ifndef SRC_COMMANDS_ARMAUTO_H_
#define SRC_COMMANDS_ARMAUTO_H_

#include <Commands/Command.h>
#include "Robot.h"
#include "Subsystems/Arm.h"


struct ArmPosition {
	// placeholder
	static constexpr double Scale = Arm::CHAIN_RATIO * 0.4;
	// two feet up
	static constexpr double Switch = Arm::CHAIN_RATIO*24/(Arm::LENGTH*2*M_PI); 
};

class MoveArmTo : public frc::Command {
public:
	double to;
	MoveArmTo(double to): to(to) {};
	void Initialize() override { Robot::arm.MoveTo(to); }
	bool IsFinished() override { return Robot::arm.OnTarget(); }
};

class MoveClaw : public frc::InstantCommand {
public:
	enum ClawPosition {
		Open,
		Closed
	};
	
	ClawPosition to;
	MoveClaw(ClawPosition to): to(to) {};
	void Initialize() override { (to == Open) ? Robot::claw.Open() : Robot::claw.Close(); };
};
class MoveWrist : public frc::InstantCommand {
public:
	enum WristPosition {
		Up,
		Down
	};
	
	WristPosition to;
	MoveWrist(WristPosition to): to(to) {};
	void Initialize() override { (to == Up) ? Robot::wrist.Up() : Robot::wrist.Down(); };
};

constexpr double TICKS_PER_SECOND = 50;
class ArmForTime : public frc::Command {
public:
	
	double power;
	double time;
	
	int ticks;
	
	ArmForTime(double power, double time): power(power), time(time) {};
	
	void Execute() override { ticks++; Robot::arm.Move(power); }
	bool IsFinished() override { if (ticks >= time * TICKS_PER_SECOND) {  Robot::arm.Move(0); return true; } else return false; }
};


#endif /* SRC_COMMANDS_ARMAUTO_H_ */
