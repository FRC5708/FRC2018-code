#include <Commands/MoveToPoint.h>
#include <iostream>


MoveToPoint::MoveToPoint(Point* location, Point to): location(location), to(to) {
	turnCommand = new TurnAngle(0);
	AddSequential(turnCommand);
	driveCommand = new DriveDistance(0);
	AddSequential(driveCommand);
}

MoveToPoint::~MoveToPoint() {
}

void MoveToPoint::Initialize() {
	CommandGroup::Initialize();
	
	std::cout << "moving to point: (" << to.x << ", " << to.y << ")" << std::endl;
		
		double x = to.x - location->x;
		double y = to.y - location->y;
		turnCommand->angle = (atan(x / y) * 180 / M_PI);
}

void MoveToPoint::Execute() {
	if (turnCommand != nullptr) {
		if (turnCommand->IsFinished()) {
			double x = to.x - location->x;
			double y = to.y - location->y;
			driveCommand->inchesToDrive = sqrt(x*x + y*y);
			
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
