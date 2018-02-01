#ifndef ClawWithJoystick_H
#define ClawWithJoystick_H

#include <Commands/Command.h>
#include <OI.h>
#include <Joystick.h>
#include <RobotMap.h>
#include <vector>

class ClawWithJoystick : public frc::Command {
private:
	enum clawMode {OPEN,CLOSE,STOP};
	clawMode mode = STOP;
	std::vector<bool> buttons = std::vector<bool>(12);
	joystickMode joyMode = XBOX;
public:
	ClawWithJoystick();
	void Initialize(){};
	bool WasButtonJustPressed(int button);
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted(){};
};

#endif  // ClawWithJoystick_H
