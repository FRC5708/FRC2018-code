#ifndef ReleaseHook_H
#define ReleaseHook_H

#include <Commands/Command.h>

class ReleaseHook : public frc::Command {
public:
	ReleaseHook();
	void Initialize() {}
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted() {};
};

#endif  // ReleaseHook_H
