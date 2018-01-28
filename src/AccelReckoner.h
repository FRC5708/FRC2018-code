

#ifndef SRC_ACCELRECKONER_H_
#define SRC_ACCELRECKONER_H_

#include <BuiltInAccelerometer.h>
#include <AnalogGyro.h>
#include <chrono>
#include "RobotMap.h"

class AccelReckoner {
public:
	AccelReckoner();
	void Calibrate();
	void Periodic();
	
	double locX, locY, locZ; // inches
	
private:
	
	Accelerometer* accelerometer = new BuiltInAccelerometer();
	AnalogGyro* gyro = new AnalogGyro(gyroChannel);
	
	double gravX, gravY, gravZ;
	//std::chrono::time_point prevTime;
	
};

#endif /* SRC_ACCELRECKONER_H_ */
