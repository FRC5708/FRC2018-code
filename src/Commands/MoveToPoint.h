#ifndef SRC_COMMANDS_MOVETOPOINT_H_
#define SRC_COMMANDS_MOVETOPOINT_H_

#include <Commands/CommandGroup.h>
#include "AutoCommand.h"
#include "TurnAngle.h"
#include "DriveDistance.h"
#include <memory>

class MoveToPoint : public frc::CommandGroup {
public:
	MoveToPoint(Point* location, Point to, bool backwards);
	virtual ~MoveToPoint();
	
	void Initialize() override;
	
	Point* location; // points to current location point in AutoCommand
	Point to;
	
	void Execute() override;
	bool IsFinished() override;
	
private:
	TurnAngle* turnCommand = nullptr;
	DriveDistance* driveCommand = nullptr;
	bool backwards = false;
};

#endif /* SRC_COMMANDS_MOVETOPOINT_H_ */
