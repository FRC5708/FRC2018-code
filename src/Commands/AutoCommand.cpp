/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/CommandGroup.h>
#include <Commands/CubeShoot.h>
#include <math.h>
#include <iostream>

#include "Commands/DriveDistance.h"
#include "Commands/TurnAngle.h"
#include "Commands/ArmAuto.h"
#include "Commands/WinchAuto.h"
#include "Commands/AutoCommand.h"
#include "RobotMap.h"

#include <chrono>
#include <thread>


void AutoCommand::MoveToPoint(Point to, bool backwards, double timeout) {
	std::cout << "adding point: (" << to.x << ", " << to.y << ")" << std::endl;
	
	double x = to.x - location.x;
	double y = to.y - location.y;
	
	double angle = atan(x / y) * 180 / M_PI;
	double distance = sqrt(x*x + y*y);
	
	if (backwards) {
		angle += 180;
		if (angle >= 360) angle -= 360;
		if (angle > 180) angle -= 360;
		
		distance = -distance;
	}
	
	drivingCommands->AddSequential(new TurnAngle(angle));
	//AddSequential(new frc::WaitCommand(0.2));
	drivingCommands->AddSequential(new DriveDistance(distance, timeout));

	location = to;
}

// Called just before this Command runs the first time
void AutoCommand::Initialize() {
	Robot::gyro->Reset();
}

void AutoCommand::SetupRoute() {

	// 48 in == width of portal, which robot will sit up against
	switch (robotPosition) {
	case 'L': location = { -(132 - robotWidth/2.0), robotLength/2.0 }; break;
	case 'R': location = { 132 - robotWidth/2.0, robotLength/2.0 }; break;

	case 'C': 
	default:
		location = { 0, robotLength/2.0 }; 
	}

	for (auto i = modeList.begin(); i != modeList.end(); ++i) {

		if (modePossible(*i)) {
			mode = *i;
			break;
		}
	}
	if (mode == AutonMode::eitherSwitch) {
		mode = (scorePositions[0] == 'L' ? AutonMode::leftSwitch : AutonMode::rightSwitch);
	}
	if (mode == AutonMode::eitherScale) {
		mode = (scorePositions[1] == 'L' ? AutonMode::leftScale : AutonMode::rightScale);
	}
	std::cout << "executing autonomous command " << (int) mode << std::endl;

	 
	if (mode == AutonMode::nothing) return;

	else if (mode == AutonMode::crossLine) {
		AddSequential(new DriveDistance(11*12));
		//shootingCommands->AddSequential(new CubeShoot());
	}
	else {
		
		//AddParallel(new MoveWrist(MoveWrist::Down));

		// switch
		/*else if ((robotPosition == 'C' && (mode == AutonMode::leftSwitch || mode == AutonMode::rightSwitch))
			|| (robotPosition == 'L' && mode == AutonMode::leftSwitch)
			|| (robotPosition == 'R' && mode == AutonMode::rightSwitch)) {*/
		if (mode == AutonMode::leftSwitch || mode == AutonMode::rightSwitch || mode == AutonMode::sideSwitch) {
			
			if (mode == AutonMode::sideSwitch) {
				double pos_mult = 1;
				if (robotPosition == 'L') pos_mult = -1;
				
				MoveToPoint({location.x, 14*12 }); // center of switch
				MoveToPoint({(6*12 + robotLength / 2.0) * pos_mult, location.y }, false, 2.0);
			}
			else {
				double pos_mult = 1;
				if (mode == AutonMode::leftSwitch) pos_mult = -1;

				MoveToPoint({ location.x, location.y + 1.5*12.0 }); // move forward so wall is not hit while turning

				MoveToPoint({ 4.5*12.0 * pos_mult, 6*12 });
				//drivingCommands->AddParallel(new MoveArmTo(ArmPosition::Switch));
				MoveToPoint({ location.x, 12*12 - robotLength/2.0 - 3.0 }, false, 2.0);
			}

			//shootingCommands->AddSequential(new WinchForTime(0.5, -1.0));
			shootingCommands->AddSequential(new CubeShoot());
			shootingCommands->AddSequential(new MoveClaw(MoveClaw::Open));
		}
		// scale
		else if (mode == AutonMode::leftScale || mode == AutonMode::rightScale) {
			
			// after the main "drive down field to scale" command starts, time to wait to raise arm. Roughly estimated.
			//double waitTime;
			
			double pos_mult = 1;
			if (mode == AutonMode::leftScale) pos_mult = -1;

			if ((robotPosition == 'L' && mode == AutonMode::rightScale)
			|| (robotPosition == 'R' && mode == AutonMode::leftScale)) {

				// cross arcade horizontally
				MoveToPoint({ location.x, 228 }); 
				MoveToPoint({ 9*12*pos_mult, location.y });
				
				//waitTime = 0;
			}			
			else if (robotPosition == 'C') {
				MoveToPoint({ location.x, location.y + 1.5*12.0 }); // move forward so wall is not hit while turning
				MoveToPoint({ 9*12*pos_mult, 100 }); // to side of arcade
				
				//waitTime = 2;
			}
			else {
				//waitTime = 4;
			}
			/*
			CommandGroup* armMoveCommands = new CommandGroup();
			armMoveCommands->AddSequential(new WaitCommand(waitTime));
			armMoveCommands->AddSequential(new MoveArmTo(ArmPosition::Scale));
			drivingCommands->AddParallel(armMoveCommands);*/
			
			MoveToPoint({ location.x, 299.65 + 2*12 }); //next to scale
			MoveToPoint({ (7.5*12.0 + robotLength/2.0) * pos_mult, location.y }, true);
			
		}
		
		// behind switch
			/*
			else if ((robotPosition == 'L' && mode == AutonMode::leftSwitch)
					|| (robotPosition == 'R' && mode == AutonMode::rightSwitch)) {

				double pos_mult = 1;
				if (mode == AutonMode::leftSwitch) pos_mult = -1;

				MoveToPoint({ location.x, 19.5*12.0 });
				MoveToPoint({ 10.5*12.0 * pos_mult, location.y });
				MoveToPoint({ location.x, 196 + robotLength/2 });
				// place cube
			}*/
			
		AddSequential(drivingCommands);
		AddSequential(shootingCommands);
	}
}

bool AutoCommand::modePossible(AutonMode mode) {
	switch (mode) {
	case AutonMode::leftSwitch:
		return scorePositions[0] == 'L';
	case AutonMode::rightSwitch:
		return scorePositions[0] == 'R';

	case AutonMode::leftScale:
		return scorePositions[1] == 'L';
	case AutonMode::rightScale:
		return scorePositions[1] == 'R';
		
	case AutonMode::sideSwitch:
		return scorePositions[0] == robotPosition;

	case AutonMode::eitherScale:
	case AutonMode::eitherSwitch:
	case AutonMode::crossLine:
	case AutonMode::nothing:
		return true;

	default:
		return false;
	}

}

// Called repeatedly when this Command is scheduled to run
//void MyAutoCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool AutoCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutoCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoCommand::Interrupted() {}
