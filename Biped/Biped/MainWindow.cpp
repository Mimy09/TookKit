#include "MainWindow.h"
MainWindow::MainWindow()
	: placingWall(false), deletingObjects(false), moveingObject(false), m_movingObjectIndex(-1), m_movingObjectType(0){
	m_WhiteBrush = NULL;
	m_RedBrush = NULL;
	m_FadedRedBrush = NULL;
	m_GrayBrush = NULL;
	m_GreenBrush = NULL;
	m_NodeBrush = NULL;
	m_BlueBrush = NULL;
	m_PurpleBrush = NULL;
#ifdef BPD_DEBUGMODE
	m_debugMode = 4;
	db_mode1 = db_mode2 = true;
	db_mode3 = db_mode4 = db_mode5 = false;
#endif
	m_lookatNodeIndex = -1;
}
MainWindow::~MainWindow(){}

void MainWindow::OnMouseDown(int x, int y, UINT param){
	if(param == 5){
		for(int i = 0; i < m_nodePos.size(); i++){
			if(m_nodePos[i].distance(bpd::Point(x, y)) < 10){
				m_nodePos.erase(i); break;
			}
		}
		for(int i = 0; i < m_wallPos.size(); i++){
			if(m_wallPos[i].pos.distance(bpd::Point(x, y)) < 40){
				m_wallPos.erase(i); break;
			}
		}
	} else if(param == 9){
		int xpos = ((x + 40 / 2) / 40) * 40;
		int ypos = ((y + 40 / 2) / 40) * 40;
		m_wallPos.push_back(Wall(bpd::Point(xpos, ypos), 40));
	} else if(param == 1){
		bool k = false;
		for(int i = 0; i < m_nodePos.size(); i++){
			if(m_nodePos[i].distance(bpd::Point(x, y)) < 10){
				if(m_lookatNodeIndex == i){ m_lookatNodeIndex = -1; k = true; break; }
				m_lookatNodeIndex = i;
				k = true; break;
			}
		}
		int xpos = ((x + 10 / 2) / 10) * 10;
		int ypos = ((y + 10 / 2) / 10) * 10;
		if(k == false) {
			m_nodePos.push_back(bpd::Point(xpos, ypos));
			m_lookatNodeIndex = -1;
		}
	} else if(param == 2){
		moveingObject = true;
		for(int i = 0; i < m_nodePos.size(); i++){
			if(m_nodePos[i].distance(bpd::Point(x, y)) < 10){
				m_movingObjectType = 1;
				m_movingObjectIndex = i;
				break;
			}
		}
		for(int i = 0; i < m_wallPos.size(); i++){
			if(m_wallPos[i].pos.distance(bpd::Point(x, y)) < 40){
				m_movingObjectType = 2;
				m_movingObjectIndex = i;
				break;
			}
		}
	}
}
void MainWindow::OnMouseUp(int x, int y, UINT param){
	if(param == 0){
		moveingObject = false;
		m_movingObjectIndex = -1;
		m_movingObjectType = 0;
	}
}
void MainWindow::OnKeyUp(UINT key){
	if(key == 17){ placingWall = false; } else if(key == 16){ deletingObjects = false; }
}
void MainWindow::OnMouseMove(int x, int y, UINT param){
	m_mousePos.x = x; m_mousePos.y = y;
	if(moveingObject && m_movingObjectIndex != -1){
		if(m_movingObjectType == 1){
			int xpos = ((x + 10 / 2) / 10) * 10;
			int ypos = ((y + 10 / 2) / 10) * 10;

			m_nodePos[m_movingObjectIndex].x = xpos;
			m_nodePos[m_movingObjectIndex].y = ypos;
		} else if(m_movingObjectType == 2){
			int xpos = ((x + 20 / 2) / 20) * 20;
			int ypos = ((y + 20 / 2) / 20) * 20;

			m_wallPos[m_movingObjectIndex].pos.x = xpos;
			m_wallPos[m_movingObjectIndex].pos.y = ypos;
			m_wallPos[m_movingObjectIndex].UpdateColliders();
		}
	}
}
void MainWindow::OnKeyDown(UINT key){
	if(key == 17){ placingWall = true; } else if(key == 16){ deletingObjects = true; }
	if(key == 'Q'){
		if(!m_nodePos.empty())m_nodePos.clear();
		if(!m_wallPos.empty())m_wallPos.clear();
	}
	if(key == 'W'){ if(!m_wallPos.empty())m_wallPos.clear(); }
	if(key == 'E'){ if(!m_nodePos.empty())m_nodePos.clear(); }
#ifdef BPD_DEBUGMODE
	if(key == '1'){ db_mode1 = !db_mode1; }
	if(key == '2'){ db_mode2 = !db_mode2; }
	if(key == '3'){ db_mode3 = !db_mode3; }
	if(key == '4'){ db_mode4 = !db_mode4; }
	if(key == '5'){ db_mode5 = !db_mode5; }
#endif
	if(key == 32){
		for(int i = 0; i < m_nodePos.size(); i++){
			if(m_nodePos[i].distance(bpd::Point(m_mousePos.x, m_mousePos.y)) < 10){
				m_endNodeIndex = i; break;
			}
		}
	}
}

void MainWindow::Update(double deltaTime){
	if(m_timer.SetFPS(1)){
		printf(" >> FPS: %i\n", m_timer.GetFPS());
	}

	InvalidateRect(hwnd(), NULL, FALSE);
	UpdateWindow(hwnd());
}

void MainWindow::OnDiscardDeviceResources(){
	bpd::SafeRelease(&m_WhiteBrush);
	bpd::SafeRelease(&m_RedBrush);
	bpd::SafeRelease(&m_FadedRedBrush);
	bpd::SafeRelease(&m_GrayBrush);
	bpd::SafeRelease(&m_GreenBrush);
	bpd::SafeRelease(&m_NodeBrush);
	bpd::SafeRelease(&m_BlueBrush);
	bpd::SafeRelease(&m_PurpleBrush);
}
void MainWindow::OnDeviceResources(ID2D1HwndRenderTarget* rt){
	rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&m_WhiteBrush
	);
	rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red),
		&m_RedBrush
	);
	rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red, 0.3f),
		&m_FadedRedBrush
	);
	rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Gray),
		&m_GrayBrush
	);
	rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Green),
		&m_GreenBrush
	);
	rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Green),
		&m_NodeBrush
	);
	rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue),
		&m_BlueBrush
	);
	rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Purple),
		&m_PurpleBrush
	); 
#ifndef BPD_DEBUGMODE
	m_NodeBrush->SetOpacity(0.3f);
	m_PurpleBrush->SetOpacity(0.8f);
	m_GreenBrush->SetOpacity(0.3f);
	m_RedBrush->SetOpacity(0.3f);
#endif
}

void MainWindow::OnPaint(ID2D1HwndRenderTarget* rt){
	m_timer.calcFPS();
	rt->SetTransform(D2D1::Matrix3x2F::Identity());
	rt->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	D2D1_SIZE_F rtSize = rt->GetSize();
	int width = static_cast<int>(rtSize.width);
	int height = static_cast<int>(rtSize.height);
	DrawGrid(rt, rtSize, width, height);

	if(!m_wallPos.empty()){
		for(int i = 0; i < m_wallPos.size(); i++){
			D2D1_RECT_F wall = D2D1::Rect(
				m_wallPos[i].pos.x - 40.f, m_wallPos[i].pos.y - 40.f,
				m_wallPos[i].pos.x + 40.f, m_wallPos[i].pos.y + 40.f
			); rt->FillRectangle(&wall, m_GrayBrush);
#ifdef BPD_DEBUGMODE
			if(db_mode4){
				rt->DrawLine(
					D2D1::Point2F(m_wallPos[i].seg1.x, m_wallPos[i].seg1.y),
					D2D1::Point2F(m_wallPos[i].seg1.vecX, m_wallPos[i].seg1.vecY),
					m_RedBrush, 1.0f, 0
				);
				rt->DrawLine(
					D2D1::Point2F(m_wallPos[i].seg2.x, m_wallPos[i].seg2.y),
					D2D1::Point2F(m_wallPos[i].seg2.vecX, m_wallPos[i].seg2.vecY),
					m_RedBrush, 1.0f, 0
				);
			}
#endif
		}
	}
	if(!m_nodePos.empty()){
		for(int i = 0; i < m_nodePos.size(); i++){
			for(int j = 0; j < m_nodePos.size(); j++){
				int collided = false;
				if(m_nodePos[i] == m_nodePos[j]) continue;
				if(m_nodePos[i].distance(m_nodePos[j]) <= 200){
					for(int k = 0; k < m_wallPos.size(); k++){
						if(m_nodePos[i].distance(m_wallPos[k].pos) <= 200){
							bpd::Segment temp(m_nodePos[i].x, m_nodePos[i].y, m_nodePos[j].x, m_nodePos[j].y);
#ifdef BPD_DEBUGMODE
							if(db_mode5 && m_lookatNodeIndex == -1){
								rt->DrawLine(
									D2D1::Point2F(m_nodePos[i].x, m_nodePos[i].y),
									D2D1::Point2F(m_wallPos[k].pos.x, m_wallPos[k].pos.y),
									m_BlueBrush, 1.0f, 0
								);
							} else if(m_lookatNodeIndex == i && db_mode5){
								rt->DrawLine(
									D2D1::Point2F(m_nodePos[i].x, m_nodePos[i].y),
									D2D1::Point2F(m_wallPos[k].pos.x, m_wallPos[k].pos.y),
									m_BlueBrush, 1.0f, 0
								);
							}
#endif
							if(temp.intersect(m_wallPos[k].seg1) == true || temp.intersect(m_wallPos[k].seg2) == true){
								collided = true;
							}
						}
					}
					if(collided){
#ifdef BPD_DEBUGMODE
						if(db_mode3 && m_lookatNodeIndex == -1){
							rt->DrawLine(
								D2D1::Point2F(m_nodePos[i].x, m_nodePos[i].y),
								D2D1::Point2F(m_nodePos[j].x, m_nodePos[j].y),
								m_RedBrush, 1.0f, 0
							);
						} else if(m_lookatNodeIndex == i && db_mode3){
							rt->DrawLine(
								D2D1::Point2F(m_nodePos[i].x, m_nodePos[i].y),
								D2D1::Point2F(m_nodePos[j].x, m_nodePos[j].y),
								m_RedBrush, 1.0f, 0
							);
						}
#endif
						continue;
					}
#ifdef BPD_DEBUGMODE
					if(db_mode2 && m_lookatNodeIndex == -1){
						rt->DrawLine(
							D2D1::Point2F(m_nodePos[i].x, m_nodePos[i].y),
							D2D1::Point2F(m_nodePos[j].x, m_nodePos[j].y),
							m_NodeBrush, 1.0f, 0
						);
					} else if(m_lookatNodeIndex == i && db_mode2){
						rt->DrawLine(
							D2D1::Point2F(m_nodePos[i].x, m_nodePos[i].y),
							D2D1::Point2F(m_nodePos[j].x, m_nodePos[j].y),
							m_NodeBrush, 1.0f, 0
						);
					}
#else
					if(m_lookatNodeIndex == -1){
						rt->DrawLine(
							D2D1::Point2F(m_nodePos[i].x, m_nodePos[i].y),
							D2D1::Point2F(m_nodePos[j].x, m_nodePos[j].y),
							m_NodeBrush, 1.0f, 0
						);
					}
#endif
				}
			}
#ifdef BPD_DEBUGMODE
			if(db_mode1){
				D2D1_ELLIPSE node = D2D1::Ellipse(
					D2D1::Point2F(m_nodePos[i].x, m_nodePos[i].y),
					10.f, 10.f
				);
				if(m_endNodeIndex != i){ rt->FillEllipse(&node, m_GreenBrush); } else{ rt->FillEllipse(&node, m_PurpleBrush); }
				if(m_lookatNodeIndex == i) rt->DrawEllipse(&node, m_RedBrush);
			}
#else
			D2D1_ELLIPSE node = D2D1::Ellipse(
				D2D1::Point2F(m_nodePos[i].x, m_nodePos[i].y),
				10.f, 10.f
			);
			if(m_endNodeIndex != i){ rt->FillEllipse(&node, m_GreenBrush); } else{ rt->FillEllipse(&node, m_PurpleBrush); }
			if(m_lookatNodeIndex == i) rt->DrawEllipse(&node, m_RedBrush);
#endif
		}
	}
	
	if(placingWall){
		D2D1_RECT_F tempWall = D2D1::Rect(
			m_mousePos.x - 40.f, m_mousePos.y - 40.f,
			m_mousePos.x + 40.f, m_mousePos.y + 40.f
		); rt->FillRectangle(&tempWall, m_FadedRedBrush);
	} else if(deletingObjects){
		rt->DrawLine(
			D2D1::Point2F(m_mousePos.x - 10.f, m_mousePos.y + 10.f),
			D2D1::Point2F(m_mousePos.x + 10.f, m_mousePos.y - 10.f),
			m_FadedRedBrush, 5.0f, 0
		);
		rt->DrawLine(
			D2D1::Point2F(m_mousePos.x + 10.f, m_mousePos.y + 10.f),
			D2D1::Point2F(m_mousePos.x - 10.f, m_mousePos.y - 10.f),
			m_FadedRedBrush, 5.0f, 0
		);
	} else{
		D2D1_ELLIPSE node = D2D1::Ellipse(
			D2D1::Point2F(m_mousePos.x, m_mousePos.y),
			10.f, 10.f
		); rt->FillEllipse(&node, m_FadedRedBrush);
	}
	{
		const WCHAR m_GameText[] = L"---- A* Testing Area ----\n[Q] =\t\tClear All\n[W] =\t\tClear Walls\n[E] =\t\tClear Nodes\n[LShift] =\tDelete Mode\n[LCtrl] =\tWall Mode\n[LClick] =\tPlace Object\n[RClick] =\tMove Object\n[space] =\tSelect End Node";
		rt->DrawText(
			m_GameText,
			BPD_SIZEOF(m_GameText),
			m_pDebugTextFormat,
			D2D1::RectF(0, 0, 400, 200),
			m_WhiteBrush
		);
#ifdef BPD_DEBUGMODE
		const WCHAR m_debugText[] = L"---- Debug Binds ----\n[1] =\t\tShow Nodes\n[2] =\t\tShow Node Connectors\n[3] =\t\tShow Collision Lines\n[4] =\t\tShow Box Collider\n[5] =\t\tShow What Nodes Check";
		rt->DrawText(
			m_debugText,
			BPD_SIZEOF(m_debugText),
			m_pDebugTextFormat,
			D2D1::RectF(0,height, 400, height - 100),
			m_WhiteBrush
		);
#endif // !BPD_DEBUGMODE
	}
}

void MainWindow::DrawGrid(ID2D1HwndRenderTarget* rt, D2D1_SIZE_F rtSize, int width, int height){
	for(int x = 0; x < width; x += 10){
		if(x % 40 == 0){
			rt->DrawLine(
				D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
				D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
				m_WhiteBrush, 0.3f
			);
		} else{
			rt->DrawLine(
				D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
				D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
				m_WhiteBrush, 0.1f
			);
		}
	}
	for(int y = 0; y < height; y += 10){
		if(y % 40 == 0){
			rt->DrawLine(
				D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
				D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
				m_WhiteBrush, 0.3f
			);
		} else{
			rt->DrawLine(
				D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
				D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
				m_WhiteBrush, 0.1f
			);
		}
	}
}