#ifndef SRC_COMMANDS_CUBESHOOT_H_
#define SRC_COMMANDS_CUBESHOOT_H_

#include <Commands/Command.h>
#include "Robot.h"
#include "Subsystems/Claw.h"
#include <chrono>

class CubeShoot : public frc::Command {
public:
	CubeShoot(){};
	
	void Initialize() override {
		startTime = std::chrono::steady_clock::now();
		Robot::claw.SetMove(MotorMove::FORWARD);
	}
	void Execute() override {
		if (std::chrono::steady_clock::now() > startTime + std::chrono::milliseconds(500)) {
			Robot::claw.SetMove(MotorMove::STOP);
		}
	}
	bool IsFinished() override {
		if(Robot::claw.currentMove == MotorMove::STOP) {
			return true;
		}
		return false;
	}
private:
	std::chrono::steady_clock::time_point startTime;
};



#endif /* SRC_COMMANDS_CUBESHOOT_H_ */
