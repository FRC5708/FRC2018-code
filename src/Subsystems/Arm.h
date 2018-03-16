#ifndef SRC_SUBSYSTEMS_ARM_H_
#define SRC_SUBSYSTEMS_ARM_H_

#include <SpeedController.h>
#include <PIDController.h>
#include <Encoder.h>
#include <Commands/Subsystem.h>


/* Using the arm on this branch may damage motor controllers. Stall current of 
 * MiniCIM is 89A, max continuous current of most motor controllers is 60A. 
 * Holding the arm still "stalls" the motor. Jaguar shuts off if it is over 
 * current, Spark does not. Not completely sure how big of an issue this is.
*/
class Arm: public Subsystem, PIDOutput {
public:
	Arm();
	virtual ~Arm();
	void Move(double power);
	void MoveTo(double motorRevolutions);
	void CancelMoveTo() { positionController.Disable(); isHolding = false; }
	void StartHold() { MoveTo(encoder.GetDistance()); isHolding = true; }
	bool OnTarget() { return positionController.OnTarget(); }
	
	void Periodic() override;
	
	frc::SpeedController* motor1;
	frc::SpeedController* motor2;
	frc::Encoder encoder;
	
	bool isHolding = false;
	
	static constexpr double CHAIN_RATIO = 4;
	static constexpr double LENGTH = 40; // inches
	
	bool wristHelping = true;
	
private:
	PIDController positionController;
	
	//double minPower = -1; // for gentle lowering
	
protected:
	void PIDWrite(double power) override { Move(power); };
};

#endif /* SRC_SUBSYSTEMS_ARM_H_ */
