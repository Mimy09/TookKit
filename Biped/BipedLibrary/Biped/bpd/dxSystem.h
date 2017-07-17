#pragma once
#ifndef _DXSYSTEM_H_
#define _DXSYSTEM_H_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "dxInput.h"
#include "dxGraphics.h"

BPD_BEGIN
class dxSystem {
public:
	dxSystem();
	dxSystem(const dxSystem&);
	~dxSystem();

	bool initialize();
	void shutdown();
	void run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
private:
	bool frame();
	void initalizeWindow(int&, int&);
	void shutdownWindow();
private:
	char* m_appName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	dxInput* m_input;
	dxGraphics* m_graphics;
};
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static dxSystem* ApplicationHandle = 0;
BPD_END
#endif // !_SYSTEMCLASS_H_