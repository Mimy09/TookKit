#include <iostream>
#include "bpd\dxSystem.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	
	bpd::dxSystem *System;

	bool result;


	// Create the system object.
	System = new bpd::dxSystem;
	if (!System) {
		return 0;
	}

	// Initialize and run the system object.
	result = System->initialize();
	if (result) {
		System->run();
	}

	// Shutdown and release the system object.
	System->shutdown();
	delete System;
	System = 0;



	return 0;
}