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
		nothing,
		crossLine,
		
		
		leftSwitch,
		eitherSwitch,
		rightSwitch,
		
		leftScale,
		rightScale,
		eitherScale
	};

class MyAutoCommand : public frc::CommandGroup {
public:
	

	char robotPosition; // L, R, or C
	std::string scorePositions;

	// list of modes from highest priority to lowest
	std::vector<AutonMode> modeList;
	
	
	MyAutoCommand(char robotPosition, std::string scorePositions, std::vector<AutonMode> modes): 
		robotPosition(robotPosition), scorePositions(scorePositions), modeList(modes) {};
	
	void Initialize() override;
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
	
	bool modePossible(AutonMode mode);
	AutonMode mode = AutonMode::nothing;
	

	// In inches. Position of center of robot from bottom-left of field. Bottom = alliance wall side. 
	// Only used in beginning for route calculation.
	Point location = {0, 0};
	
	void MoveToPoint(Point to);
};




