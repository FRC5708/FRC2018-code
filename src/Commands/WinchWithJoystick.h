#ifndef WinchWithJoystick_H
#define WinchWithJoystick_H

#include <commands/Command.h>

class WinchWithJoystick : public frc::Command {
public:
	WinchWithJoystick();
	void Execute() override;
	bool IsFinished() override;
	void End() override;
};

#endif  // WinchWithJoystick_H
