#ifndef SRC_SUBSYSTEMS_ARM_H_
#define SRC_SUBSYSTEMS_ARM_H_

#include <SpeedController.h>
#include <Encoder.h>

class Arm {
public:
	Arm();
	virtual ~Arm();
	
	frc::SpeedController* motor1;
	frc::SpeedController* motor2;
	
	frc::Encoder encoder;
};

#endif /* SRC_SUBSYSTEMS_ARM_H_ */
