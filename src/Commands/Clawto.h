#ifndef SRC_COMMANDS_CLAWTO_H_
#define SRC_COMMANDS_CLAWTO_H_

#include <Commands/Command.h>
#include "Robot.h"
#include "Subsystems/Claw.h"
#include <chrono>
#include <thread>

class Clawto : public frc::Command {
public:
	Clawto(){};
	void Initialize() override {
	Robot::claw.MoveMotors(1.0);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	Robot::claw.MoveMotors(0.0);
	}
	bool IsFinished() override{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return true;}
};



#endif /* SRC_COMMANDS_CLAWTO_H_ */
