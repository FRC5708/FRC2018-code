#ifndef SRC_COMMANDS_WINCHAUTO_H_
#define SRC_COMMANDS_WINCHAUTO_H_

#include <Commands/Command.h>
#include "Robot.h"
#include "Subsystems/Winch.h"


class MoveWinchTo : public frc::Command {
public:
	double to;
	MoveWinchTo(double to): to(to) {};
	void Initialize() override { Robot::winch.MoveTo(to); }
	bool IsFinished() override { return Robot::winch.OnTarget(); }
};



#endif /* SRC_COMMANDS_WINCHAUTO_H_ */
