#include "MainWindow.h"

int main(){
	MainWindow win;
	win.Create("ARandomWindow", "Window", RECT{ 0, 0, 800, 600 });
	win.Show();
	win.RunWindow();

	
}