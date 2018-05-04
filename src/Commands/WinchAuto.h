#ifndef SRC_COMMANDS_WINCHAUTO_H_
#define SRC_COMMANDS_WINCHAUTO_H_

#include <Commands/Command.h>
#include "Robot.h"
#include "Subsystems/Winch.h"
#include <chrono>


class MoveWinchTo : public frc::Command {
public:
	double to;
	MoveWinchTo(double to): to(to) {};
	void Initialize() override { Robot::winch.MoveTo(to); }
	bool IsFinished() override { return Robot::winch.OnTarget(); }
};



class WinchForTime : public frc::Command {
public:
	double time;
	double power;
	
	WinchForTime(double time, double power): time(time), power(power) {};
	
	void Initialize() override {
		startTime = std::chrono::steady_clock::now();
	}
	void Execute() override {
			Robot::winch.CancelMoveTo();
			Robot::winch.SetMotors(power);
	}
	bool IsFinished() override {
		if (std::chrono::steady_clock::now() > startTime + std::chrono::nanoseconds((int) (time * 1000000000))) {
			Robot::winch.SetMotors(0);
			return true;
		}
		return false;
	}
private:
	std::chrono::steady_clock::time_point startTime;
};



#endif /* SRC_COMMANDS_WINCHAUTO_H_ */
