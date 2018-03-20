#ifndef ClawWithJoystick_H
#define ClawWithJoystick_H

#include <Commands/Command.h>
#include <Joystick.h>
#include <Misc.h>
#include <RobotMap.h>
#include <vector>

class ClawWithJoystick : public frc::Command {
public:
	ClawWithJoystick();
	void Initialize(){};
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted(){};
	bool wrist_is_up = false;
	bool claw_is_open = false;
	bool holding_arm = false;
	double arm_power=0.0;
};

#endif  // ClawWithJoystick_H
