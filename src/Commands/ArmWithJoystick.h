#ifndef ClawWithJoystick_H
#define ClawWithJoystick_H

#include <Commands/Command.h>
#include <OI.h>
#include <Joystick.h>
#include <RobotMap.h>
#include <vector>

class ArmWithJoystick : public frc::Command {
public:
	ArmWithJoystick();
	void Initialize(){};
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted(){};
};

#endif  // ClawWithJoystick_H
