#ifndef TurnAngle_H
#define TurnAngle_H

#include <Commands/Command.h>
#include "../Robot.h"

class TurnAngle : public frc::Command {
public:
	TurnAngle(double angle);
	void Initialize();
	bool IsFinished();
	void End();

	class TurnAnglePIDSource : public frc::PIDSource {
		public:
			virtual ~TurnAnglePIDSource() = default;
			double PIDGet() override;
		};

	class TurnAnglePIDOutput : public frc::PIDOutput {
		public:
			virtual ~TurnAnglePIDOutput() = default;
			void PIDWrite(double d) override;
	};

	private:
		TurnAnglePIDSource source;
		TurnAnglePIDOutput output;
		frc::PIDController pid{0.1, 0.001, 0, source, output};
};

#endif  // TurnAngle_H
