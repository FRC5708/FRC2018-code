#include "SelfControl.h"
#include <LibDS/include/LibDS.h>


using namespace SelfControl;

bool SelfControl::initialized = false;
void SelfControl::Enable() {
	if (!initialized) Init();
	
	DS_SetRobotEnabled(true);
}

void SelfControl::Init() {
	
	DS_Init();
	DS_SetCustomRobotAddress("127.0.0.1");
	
	DS_Protocol protocol = DS_GetProtocolFRC_2016();
	DS_ConfigureProtocol(&protocol);
	
	initialized = true;
}

void SelfControl::Close() {
	DS_Close();
}
