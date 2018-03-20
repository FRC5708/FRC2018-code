/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Misc.h>

// from 0 to inputChangePosition in joystick, power output is 0 to outputChangePosition. This makes the robot easier to control at low speeds.
double inputTransform(double input, double minPowerOutput, double inputDeadZone, 
		 double inputChangePosition, double outputChangePosition) {
	

	double output = 0;
	if (fabs(input) <= inputDeadZone) {
		output = 0;
	}
	else if (fabs(input) <= inputChangePosition) {
		output = (fabs(input) / inputChangePosition * (outputChangePosition - minPowerOutput)) + minPowerOutput;
	}
	else {
		output = (fabs(input) - inputChangePosition)
				/ (1 - inputChangePosition)
				* (1 - outputChangePosition)
				+ outputChangePosition;
	}
	if (input < 0) output = -output;
	return output;
}
