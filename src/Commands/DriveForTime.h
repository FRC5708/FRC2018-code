#ifndef DriveForTime_H
#define DriveForTime_H

#include <Commands/Command.h>
#include "../Robot.h"

class DriveForTime : public frc::Command {
private:
	int count;
	int time;
public:
	DriveForTime(int _t);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveForTime_H
