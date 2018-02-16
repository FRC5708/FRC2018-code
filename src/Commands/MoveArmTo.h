#ifndef SRC_COMMANDS_MOVEARMTO_H_
#define SRC_COMMANDS_MOVEARMTO_H_

#include <Commands/Command.h>
#include "Robot.h"


struct ArmPosition {
	// place holders
	static constexpr double ScalePosition = 1;
	static constexpr double SwitchPosition = 1;
};

class MoveArmTo : public frc::Command {
public:
	MoveArmTo(double to) { Robot::arm.MoveTo(to); }
};


#endif /* SRC_COMMANDS_MOVEARMTO_H_ */
