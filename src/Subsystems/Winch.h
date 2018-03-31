#ifndef Winch_H
#define Winch_H

#include <Commands/Subsystem.h>
#include <SpeedController.h>
#include <Encoder.h>
#include <PIDController.h>

class Winch : public frc::Subsystem, PIDOutput {
public:
	Winch();
	void SetMotors(double power);
	void MoveTo(double motorRevolutions);
	void CancelMoveTo() { positionController.Disable(); isHolding = false; }
	void StartHold() { MoveTo(encoder.GetDistance()); isHolding = true; }
	bool OnTarget() { return positionController.OnTarget(); }

	frc::SpeedController* leftMotor;
	frc::SpeedController* rightMotor;

	Encoder encoder;
	PIDController positionController;

	bool isHolding = false;
	
protected:
	void PIDWrite(double power) override { SetMotors(power); };
};

#endif  // Winch_H
