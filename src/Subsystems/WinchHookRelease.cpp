#include "WinchHookRelease.h"
#include "../RobotMap.h"

WinchHookRelease::WinchHookRelease() : Subsystem("ExampleSubsystem"),
										releaseServo(ArmReleaseChannel){

}

void WinchHookRelease::realeaseHookArm(){
	releaseServo->Set(1);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
