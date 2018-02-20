#include <Commands/MoveToPoint.h>
#include <iostream>


MoveToPoint::MoveToPoint(Point* location, Point to): location(location), to(to) {
}

MoveToPoint::~MoveToPoint() {
}

void MoveToPoint::Initialize() {
	CommandGroup::Initialize();
	
	std::cout << "moving to point: (" << to.x << ", " << to.y << ")" << std::endl;
		
		double x = to.x - location->x;
		double y = to.y - location->y;
		turnCommand = new TurnAngle(atan(x / y) * 180 / M_PI);
		AddSequential(turnCommand);
		
}

void MoveToPoint::Execute() {
	if (turnCommand != nullptr) {
		if (turnCommand->IsFinished()) {
			double x = to.x - location->x;
			double y = to.y - location->y;
			driveCommand = new DriveDistance(sqrt(x*x + y*y));
			AddSequential(driveCommand);
			turnCommand = nullptr;
		}
	}
	
	CommandGroup::Execute();
}

bool MoveToPoint::IsFinished() {
	
	return ((turnCommand == nullptr || turnCommand->IsFinished())
		&& (driveCommand == nullptr || driveCommand->IsFinished())
		) && (CommandGroup::IsFinished());
}
