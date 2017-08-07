#include <iostream>
#include "MainWindow.h"

int main(){
	try {
		HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
		if (SUCCEEDED(CoInitialize(NULL))) { {
			MainWindow window;
			window.Create("AStar_f378gf", "A* Demo", RECT{ 0, 0, 1000, 600 }, true);
			window.Show();
			window.RunWindow();
		} CoUninitialize(); }
	} catch (bpd::Exception e) { e.msgWhat(); }
	return 0;
}