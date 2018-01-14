/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "MyAutoCommand.h"
#include <Commands/CommandGroup.h>

#include <Commands/DriveForTime.h>



// Called just before this Command runs the first time
void MyAutoCommand::Initialize() {
	for (auto i = modeList.begin(); i != modeList.end(); ++i) {
		
		if (modePossible(*i)) {
			mode = *i;
			break;
		}
	}
	
	switch (mode) {
	case AutonMode::crossLine:
		AddSequential(new DriveForTime(1000));
		
		break;
	default: break;
	}
}

bool MyAutoCommand::modePossible(AutonMode mode) {
	switch (mode) {
	case AutonMode::leftSwitch:
		return scorePositions[0] == 'L';
	case AutonMode::rightSwitch:
		return scorePositions[0] == 'R';
		
	case AutonMode::leftScale:
		return scorePositions[1] == 'L';
	case AutonMode::rightScale:
		return scorePositions[1] == 'R';
			
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
bool MyAutoCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MyAutoCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MyAutoCommand::Interrupted() {}
