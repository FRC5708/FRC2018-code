/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/CommandGroup.h>
#include <string>
#include <vector>

// caller specifies prioritized list
	enum struct AutonMode {
		crossLine,
		nothing,
		
		leftSwitch,
		eitherSwitch,
		rightSwitch,
		sideSwitch,
		
		leftScale,
		rightScale,
		eitherScale
	};

class AutoCommand : public frc::CommandGroup {
public:
	

	char robotPosition; // L, R, or C
	std::string scorePositions;

	// list of modes from highest priority to lowest
	std::vector<AutonMode> modeList;
	
	
	AutoCommand(char robotPosition, std::string scorePositions, std::vector<AutonMode> modes): 
		robotPosition(robotPosition), scorePositions(scorePositions), modeList(modes) { SetupRoute(); };
	
	void Initialize() override;
	void SetupRoute();
	//void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	
	struct Point {
			double x;
			double y;
			
			Point(double x, double y): x(x), y(y) {};
		};
	
private:
	// Note: AddSequential(xyz) forces the *next* command to wait until xyz is finished. 
	// Also, CommandGroups are only considered "finished" if all commands inside are 
	// finished, no matter if they are parallel or sequential.
	
	// This group is used so the claw is only opened after the arm has moved
	frc::CommandGroup* drivingCommands = new frc::CommandGroup();
	frc::CommandGroup* shootingCommands = new frc::CommandGroup();
	
	bool modePossible(AutonMode mode);
	AutonMode mode = AutonMode::nothing;
	

	// In inches. Position of center of robot from bottom-center of field. Bottom = alliance wall side. left=negative. 
	// Only used in beginning for route calculation.
	Point location = {0, 0};
	
	void MoveToPoint(Point to, bool backwards = false, double timeout = INFINITY);
};




