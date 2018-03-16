#include <Commands/MoveToPoint.h>
#include <iostream>


MoveToPoint::MoveToPoint(Point* location, Point to, bool backwards): location(location), to(to), backwards(backwards) {
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
		
		double angle = atan(x / y) * 180.0 / M_PI;
		if (backwards) {
			angle += 180;
			if (angle >= 360) angle -= 360;
			if (angle > 180) angle -= 360;
		}
		
		turnCommand->angle = angle;
}

void MoveToPoint::Execute() {
	if (turnCommand != nullptr) {
		if (turnCommand->IsFinished()) {
			double x = to.x - location->x;
			double y = to.y - location->y;
			
			double distance = sqrt(x*x + y*y);
			if (backwards) distance = -distance;
			driveCommand->inchesToDrive = distance;
			
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
