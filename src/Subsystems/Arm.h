#ifndef SRC_SUBSYSTEMS_ARM_H_
#define SRC_SUBSYSTEMS_ARM_H_

#include <SpeedController.h>
#include <Encoder.h>
#include <Commands/Subsystem.h>

class Arm: public frc::Subsystem {
public:
	Arm();
	virtual ~Arm();
	void Move(double);
	frc::SpeedController* motor1;
	frc::SpeedController* motor2;
	frc::Encoder encoder;
};

#endif /* SRC_SUBSYSTEMS_ARM_H_ */
