#ifndef ClawWithJoystick_H
#define ClawWithJoystick_H

#include <Commands/Command.h>
#include <OI.h>
#include <Joystick.h>
#include <RobotMap.h>
#include <vector>

class ClawWithJoystick : public frc::Command {
public:
	void SetControlScheme(joystickMode);
	ClawWithJoystick();
	void Initialize(){};
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted(){};
};

#endif  // ClawWithJoystick_H
