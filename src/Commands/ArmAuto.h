#ifndef SRC_COMMANDS_ARMAUTO_H_
#define SRC_COMMANDS_ARMAUTO_H_

#include <Commands/Command.h>
#include "Robot.h"


struct ArmPosition {
	// place holders
	static constexpr double Scale = 1;
	static constexpr double Switch = 1;
};

class MoveArmTo : public frc::Command {
public:
	double to;
	MoveArmTo(double to): to(to) {};
	void Initialize() override { Robot::arm.MoveTo(to); }
	bool IsFinished() override { return true; }
};

class MoveClaw : public frc::Command {
public:
	enum ClawPosition {
		Open,
		Closed
	};
	
	ClawPosition to;
	MoveClaw(ClawPosition to): to(to) {};
	void Initialize() override { (to == Open) ? Robot::claw.Open() : Robot::claw.Close(); };
	bool IsFinished() override { return true; }
};
class MoveWrist : public frc::Command {
public:
	enum WristPosition {
		Up,
		Down
	};
	
	WristPosition to;
	MoveWrist(WristPosition to): to(to) {};
	void Initialize() override { (to == Up) ? Robot::wrist.Open() : Robot::wrist.Close(); };
	bool IsFinished() override { return true; }
};



#endif /* SRC_COMMANDS_ARMAUTO_H_ */
