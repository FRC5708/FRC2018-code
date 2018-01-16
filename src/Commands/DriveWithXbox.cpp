

#include <Commands/DriveWithXbox.h>
#include <Joystick.h>

using frc::GenericHID;

void DriveWithXbox::Execute() {
	double power = Robot::joystick->GetY(Joystick::JoystickHand::kLeftHand);
	double turn = Robot::joystick->GetX(Joystick::JoystickHand::kRightHand);
	
	Robot::drivetrain.DriveWithDirection(power, turn);
}
