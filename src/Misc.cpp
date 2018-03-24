/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Misc.h>

// From 0 to inputChangePosition in joystick, power output is 0 to outputChangePosition. 
// This makes the robot easier to control at low speeds.
// Also provides easy way to implement "dead zone" for output (minPowerOutput) and input.
double inputTransform(double input, double minPowerOutput, double inputDeadZone, 
		 double inputChangePosition, double outputChangePosition) {
	

	double output = 0;
	double correctedInput = fabs(input) - inputDeadZone;
	if (correctedInput < 0) correctedInput = 0;
	
	
	if (correctedInput <= inputChangePosition) {
		output = (correctedInput / inputChangePosition * (outputChangePosition - minPowerOutput)) + minPowerOutput;
	}
	else {
		output = (correctedInput - inputChangePosition)
				/ (1 - inputChangePosition)
				* (1 - outputChangePosition)
				+ outputChangePosition;
	}
	if (input < 0) output = -output;
	return output;
}
