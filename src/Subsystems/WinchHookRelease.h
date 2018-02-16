#ifndef WinchHookRelease_H
#define WinchHookRelease_H

#include <Commands/Subsystem.h>
#include <Servo.h>

class WinchHookRelease : public frc::Subsystem {
public:
	WinchHookRelease();
	virtual ~WinchHookRelease() {};
	void realeaseHookArm();
	frc::Servo releaseServo;

};

#endif  // WinchHookRelease_H
