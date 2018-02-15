#ifndef SRC_SUBSYSTEMS_ARM_H_
#define SRC_SUBSYSTEMS_ARM_H_

#include <SpeedController.h>
#include <PIDController.h>
#include <Encoder.h>
#include <Commands/Subsystem.h>

class Arm: public Subsystem, PIDOutput {
public:
	Arm();
	virtual ~Arm();
	void Move(double power);
	void MoveTo(double motorRevolutions);
	void CancelMoveTo() { positionController.Disable(); };
	
	frc::SpeedController* motor1;
	frc::SpeedController* motor2;
	
	frc::Encoder encoder;
	
private:
	PIDController positionController;
	
protected:
	void PIDWrite(double power) override { Move(power); };
};

#endif /* SRC_SUBSYSTEMS_ARM_H_ */
