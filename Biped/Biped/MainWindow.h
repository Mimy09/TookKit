#pragma once
#include <bpd\bpdWindow.h>
#include "bpd\bpdWinObjects.h"
#include "bpd\LinkedList.h"
#include "bpd\Maths.h"
#include "Wall.h"
#include "Node.h"
#include <iostream>

class MainWindow : public bpd::Window {
	ID2D1SolidColorBrush* m_WhiteBrush;
	ID2D1SolidColorBrush* m_RedBrush;
	ID2D1SolidColorBrush* m_GreenBrush;
	ID2D1SolidColorBrush* m_BlueBrush;
	ID2D1SolidColorBrush* m_FadedRedBrush;
	ID2D1SolidColorBrush* m_GrayBrush;
	ID2D1SolidColorBrush* m_NodeBrush;
	ID2D1SolidColorBrush* m_PurpleBrush;

	bpd::LinkedList< AINode > m_nodePos;
	bpd::LinkedList< Wall > m_wallPos;

	bool placingWall, deletingObjects, moveingObject;
	int m_movingObjectIndex, m_movingObjectType;
	int m_endNodeIndex, m_lookatNodeIndex;
	bpd::Point m_mousePos;
#ifdef BPD_DEBUGMODE
	bool db_mode1, db_mode2, db_mode3, db_mode4, db_mode5;
	int m_debugMode;
#endif
public:

	MainWindow();
	virtual ~MainWindow();

	virtual void OnMouseDown(int x, int y, UINT param);
	virtual void OnMouseUp(int x, int y, UINT param);
	virtual void OnKeyUp(UINT key);
	virtual void OnKeyDown(UINT key);
	virtual void OnMouseMove(int x, int y, UINT param);
	virtual void Update(double deltaTime);

	virtual void OnDiscardDeviceResources();
	virtual void OnDeviceResources(ID2D1HwndRenderTarget* rt);

	virtual void OnPaint(ID2D1HwndRenderTarget* rt);

	void linkNode(int index);

	void DrawGrid(ID2D1HwndRenderTarget* rt, D2D1_SIZE_F rtSize, int width, int height);
};