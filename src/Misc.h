/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "WPILib.h"
#include <Joystick.h>

double inputTransform(double input, double minPowerOutput, double inputDeadZone, 
		 double inputChangePosition = 0.75, double outputChangePosition = 0.5);
