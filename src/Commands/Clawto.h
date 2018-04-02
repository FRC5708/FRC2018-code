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
	Robot::claw.SetMove(FORWARD);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	Robot::claw.SetMove(STOP);
	}
	bool IsFinished() override{
		if(Robot::claw.currentMove==STOP){
			Robot::claw.SetMove(NONE);
			return true;
		}
		return false;}
};



#endif /* SRC_COMMANDS_CLAWTO_H_ */
