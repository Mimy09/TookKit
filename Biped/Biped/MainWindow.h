#pragma once
#include <bpd\bpdWindow.h>
#include "bpd\bpdWinObjects.h"
#include "bpd\LinkedList.h"
#include "bpd\Maths.h"
#include "Wall.h"
#include "Node.h"
#include "Flock.h"
#include <iostream>
//#include "Blackboard.h"

class MainWindow : public bpd::Window {

	//************************************
	// Brushes
	ID2D1SolidColorBrush* m_WhiteBrush;
	ID2D1SolidColorBrush* m_RedBrush;
	ID2D1SolidColorBrush* m_GreenBrush;
	ID2D1SolidColorBrush* m_BlueBrush;
	ID2D1SolidColorBrush* m_FadedRedBrush;
	ID2D1SolidColorBrush* m_GrayBrush;
	ID2D1SolidColorBrush* m_NodeBrush;
	ID2D1SolidColorBrush* m_PurpleBrush;
	//************************************


	//************************************
	// Lists
	bpd::LinkedList< AINode > m_nodePos;
	bpd::LinkedList< AINode* >  m_openNodes, m_closedNodes, m_path;
	bpd::LinkedList< Wall > m_wallPos;
	//************************************


	//************************************
	// Switch checks
	bool placingWall, deletingObjects, moveingObject;
	//************************************


	//************************************
	// Indexes
	int m_movingObjectIndex, m_movingObjectType;
	int m_endNodeIndex, m_lookatNodeIndex;
	//************************************

	//************************************
	// Private Variables
	bpd::Point m_mousePos;
	Flock flock;
	// A* Variables
	AINode* StartNode;
	AINode* EndNode;
	//************************************

	//Blackboard<int> m_blackboard;

	//************************************
	// Debug switch checks Variables
#ifdef BPD_DEBUGMODE
	bool db_mode1, db_mode2, db_mode3, db_mode4, db_mode5;
	int m_debugMode;
#endif
	//************************************

public:

	//************************************
	// Constructor / De-Constructor
	MainWindow();
	virtual ~MainWindow();
	//************************************

	//************************************
	// Overridden functions
	virtual void OnMouseDown(int x, int y, UINT param);
	virtual void OnMouseUp(int x, int y, UINT param);
	virtual void OnKeyUp(UINT key);
	virtual void OnKeyDown(UINT key);
	virtual void OnMouseMove(int x, int y, UINT param);
	virtual void Update(double deltaTime);
	virtual void OnCommand(char* command_1, char* command_2);
	virtual void OnDiscardDeviceResources();
	virtual void OnDeviceResources(ID2D1HwndRenderTarget* rt);
	virtual void OnPaint(ID2D1HwndRenderTarget* rt);
	//************************************

	void linkNode(int index);

	//************************************
	// Method:    CalcPath
	// FullName:  MainWindow::CalcPath
	// Access:    public 
	// Returns:   bpd::LinkedList<AINode*>
	// Parameter: int Start
	// Parameter: int End
	// Def: Calculates the A* path
	//************************************
	bpd::LinkedList<AINode*> CalcPath(int Start, int End);

	//************************************
	// Method:    reconstructPath
	// FullName:  MainWindow::reconstructPath
	// Access:    public 
	// Returns:   bpd::LinkedList< AINode* >
	// Parameter: AINode * cur
	// Def: Reconstructs the A* path
	//************************************
	bpd::LinkedList< AINode* > reconstructPath(AINode* cur);

	//************************************
	// Method:    DrawGrid
	// FullName:  MainWindow::DrawGrid
	// Access:    public 
	// Returns:   void
	// Parameter: ID2D1HwndRenderTarget * rt
	// Parameter: D2D1_SIZE_F rtSize
	// Parameter: int width
	// Parameter: int height
	// Def: Draws Grid
	//************************************
	void DrawGrid(ID2D1HwndRenderTarget* rt, D2D1_SIZE_F rtSize, int width, int height);


	//************************************
	// Method:    PlaceNodeGrid
	// FullName:  MainWindow::PlaceNodeGrid
	// Access:    public 
	// Returns:   void
	// Def: Creates a grid of nodes
	//************************************
	void PlaceNodeGrid();
};