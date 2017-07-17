#pragma once
#include <bpd\bpdWindow.h>

class MainWindow : public bpd::Window {
public:
	
	MainWindow(){}
	virtual ~MainWindow(){}

	virtual void Update(double deltaTime){
		if(m_timer.SetFPS(5)){
			printf("FPS: %i\n", m_timer.GetFPS());
		}
	}

	virtual void OnPaint(HDC hdc){
		bpd::WinText(hdc, "Hello World!", RECT{ 10, 10, 100, 100 });
		m_timer.calcFPS();
	}
};