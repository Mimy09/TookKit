#pragma once

class FOOBAR : public bpdApplication {
private:
	bpd::Timer* m_timer;
	HWND* m_hwnd;
public:
	virtual void Start() {
		m_hwnd = bpd::getHWND();
		m_timer = bpd::getTimer();
	}

	virtual void Draw(HDC hdc) {
		BPD_BEGIN_DRAW;
		m_timer->calcFPS();
		
		SelectObject(hdc, bpd::Brush::Red);
		Rectangle(hdc, 0, 0, 100, 100);
	}

	virtual void Update(double deltaTime) {
		if(m_timer->SetFPS(1)) { printf(" >> FPS: %i\n", m_timer->GetFPS()); }



		BPD_UPDATE_WINDOW;
	}
};