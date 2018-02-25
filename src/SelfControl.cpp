#include "SelfControl.h"
#include <LibDS/include/LibDS.h>
#include <iostream>


using namespace SelfControl;

bool SelfControl::initialized = false;
void SelfControl::Enable() {

	if (!initialized) Init();
	
	bool connected = DS_GetRobotCommunications();
	std::cerr << "Enabling robot via LibDS. Connected: " << connected << std::endl;
	DS_SetRobotEnabled(true);

}

void SelfControl::Init() {
	
	DS_Init();
	DS_SetCustomRobotAddress("127.0.0.1");
	
	DS_Protocol protocol = DS_GetProtocolFRC_2016();
	DS_ConfigureProtocol(&protocol);
	
	initialized = true;

	std::cout << "Initializing LibDS" << std::endl;
}

void SelfControl::Close() {
	DS_Close();
}
