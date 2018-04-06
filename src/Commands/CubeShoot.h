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
	}
	void Execute() override {
		Robot::claw.SetMove(MotorMove::FORWARD);
	}
	bool IsFinished() override {
		if (std::chrono::steady_clock::now() > startTime + std::chrono::milliseconds(2000)) {
			Robot::claw.SetMove(MotorMove::STOP);
			return true;
		}
		return false;
	}
		private:
	std::chrono::steady_clock::time_point startTime;
};



#endif /* SRC_COMMANDS_CUBESHOOT_H_ */
