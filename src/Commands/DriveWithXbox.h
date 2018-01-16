#include "DriveWithJoystick.h"

#ifndef SRC_COMMANDS_DRIVEWITHXBOX_H_
#define SRC_COMMANDS_DRIVEWITHXBOX_H_

class DriveWithXbox : public DriveWithJoystick {
public:
	void Execute() override;
};

#endif /* SRC_COMMANDS_DRIVEWITHXBOX_H_ */
