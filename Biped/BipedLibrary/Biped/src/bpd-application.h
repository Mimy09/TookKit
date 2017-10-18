// ################################################################## //
// ##							Application						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Sep 5 - AIE			   ## //
// ################################################################## //
#pragma once

class bpdApplication {
public:
	bpdApplication(){}
	virtual ~bpdApplication() = 0{}

	virtual void Start(){ }
	virtual void Update(double deltaTime){}
	virtual void Draw(HDC hdc){
		SelectObject(hdc, bpd::Brush::Black);
		PatBlt(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), PATCOPY);
		SelectObject(hdc, bpd::Brush::White);
	}

	//Events
	virtual void OnMouseUp(mouse& e) {}
	virtual void OnMouseDown(mouse& e){}
	virtual void OnMouseMove(mouse& e) {}

	virtual void OnKeyUp(keyboard& e) {}
	virtual void OnKeyDown(keyboard& e) {}

	virtual void OnCommand(char* arg1, char* arg2) {}
};
