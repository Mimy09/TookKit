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
	db_mode3 = db_mode1 = db_mode2 = true;
	db_mode4 = db_mode5 = false;
#endif
	m_lookatNodeIndex = -1;
}
MainWindow::~MainWindow(){}

void MainWindow::OnMouseDown(int x, int y, UINT param){
	if(param == 5){
		for(int i = 0; i < m_nodePos.size(); i++){
			if(m_nodePos[i].GetPos().distance(bpd::Point(x, y)) < 10){
				if (m_lookatNodeIndex == i) m_lookatNodeIndex = 1;
				
				for (int j = 0; j < m_nodePos.size(); j++) {
					for (int k = 0; k < m_nodePos[j].m_edges.size(); k++) {
						if (*m_nodePos[j].m_edges[k].Point1 == m_nodePos[i] ||
							*m_nodePos[j].m_edges[k].Point2 == m_nodePos[i]) {
							m_nodePos[j].m_edges.erase(k);
						}
					}
				}

				m_nodePos.erase(i);
				printf("\n---- Deleting Node ----\n");
				printf("Index: %i\n\n", i);
				break;
			}
		}
		for(int i = 0; i < m_wallPos.size(); i++){
			if(m_wallPos[i].pos.distance(bpd::Point(x, y)) < 40){
				m_wallPos.erase(i);
				printf("\n---- Deleting Wall ----\n");
				printf("Index: %i\n\n", i);
				break;
			}
		}
	} else if(param == 9){
		int xpos = ((x + 40 / 2) / 40) * 40;
		int ypos = ((y + 40 / 2) / 40) * 40;
		m_wallPos.push_back(Wall(bpd::Point(xpos, ypos), 40));
		for (int k = 0; k < m_nodePos.size(); k++) {
			if (m_nodePos[k].m_edges.size() != 0)m_nodePos[k].m_edges.clear();
			for (int i = 0; i < m_nodePos.size(); i++) {
				for (int j = 0; j < m_nodePos[i].m_edges.size(); j++) {
					if (*m_nodePos[i].m_edges[j].Point1 == m_nodePos[k] ||
						*m_nodePos[i].m_edges[j].Point2 == m_nodePos[k]) {
						m_nodePos[i].m_edges.erase(j);
					}
				}
			}
			linkNode(k);
		}
		printf("\n---- Adding Wall ----\n");
		printf("Index: %i\n", m_wallPos.size());
		printf("X:%i\tY:%i\n\n", xpos, ypos);
	} else if(param == 1){
		bool k = false;
		for(int i = 0; i < m_nodePos.size(); i++){
			if(m_nodePos[i].GetPos().distance(bpd::Point(x, y)) < 10){
				if(m_lookatNodeIndex == i){ m_lookatNodeIndex = -1; k = true; break; }
				m_lookatNodeIndex = i;
				k = true; break;
			}
		}
		int xpos = ((x + 10 / 2) / 10) * 10;
		int ypos = ((y + 10 / 2) / 10) * 10;
		if(k == false) {
			m_nodePos.push_back(AINode{ bpd::Point(xpos, ypos) });
			m_lookatNodeIndex = -1;
			linkNode(m_nodePos.size() - 1);
			printf("\n---- Adding Point ----\n");
			printf("Index: %i\n", m_nodePos.size());
			printf("X:%i\tY:%i\n", xpos, ypos);
			for (int i = 0; i < m_nodePos[m_nodePos.size() - 1].m_edges.size(); i++) {
				printf("Point1: %f, %f\n", m_nodePos[m_nodePos.size() - 1].m_edges[i].Point1->GetPos().x, m_nodePos[m_nodePos.size() - 1].m_edges[i].Point1->GetPos().y);
				printf("Point2: %f, %f\n\n", m_nodePos[m_nodePos.size() - 1].m_edges[i].Point2->GetPos().x, m_nodePos[m_nodePos.size() - 1].m_edges[i].Point2->GetPos().y);
			}
		}
	} else if(param == 2){
		moveingObject = true;
		for(int i = 0; i < m_nodePos.size(); i++){
			if(m_nodePos[i].GetPos().distance(bpd::Point(x, y)) < 10){
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
	if (param == 16) {
		for (int i = 0; i < m_nodePos.size(); i++) {
			if (m_nodePos[i].GetPos().distance(bpd::Point(x, y)) < 10) {
				m_nodePos[i].type2 = AINode::START;
				CalcPath(i, m_endNodeIndex);
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
			if (m_nodePos[m_movingObjectIndex].m_edges.size() != 0)m_nodePos[m_movingObjectIndex].m_edges.clear();
			for (int i = 0; i < m_nodePos.size(); i++) {
				for (int j = 0; j < m_nodePos[i].m_edges.size(); j++) {
					if (*m_nodePos[i].m_edges[j].Point1 == m_nodePos[m_movingObjectIndex] ||
						*m_nodePos[i].m_edges[j].Point2 == m_nodePos[m_movingObjectIndex]) {
						m_nodePos[i].m_edges.erase(j);
					}
				}
			}
			linkNode(m_movingObjectIndex);
			int xpos = ((x + 10 / 2) / 10) * 10;
			int ypos = ((y + 10 / 2) / 10) * 10;

			m_nodePos[m_movingObjectIndex].GetPos().x = xpos;
			m_nodePos[m_movingObjectIndex].GetPos().y = ypos;
		} else if(m_movingObjectType == 2){
			int xpos = ((x + 20 / 2) / 20) * 20;
			int ypos = ((y + 20 / 2) / 20) * 20;

			for (int k = 0; k < m_nodePos.size(); k++) {
				if (m_nodePos[k].m_edges.size() != 0)m_nodePos[k].m_edges.clear();
				for (int i = 0; i < m_nodePos.size(); i++) {
					for (int j = 0; j < m_nodePos[i].m_edges.size(); j++) {
						if (*m_nodePos[i].m_edges[j].Point1 == m_nodePos[k] ||
							*m_nodePos[i].m_edges[j].Point2 == m_nodePos[k]) {
							m_nodePos[i].m_edges.erase(j);
						}
					}
				}
				linkNode(k);
			}
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
		printf("\n---- Deleting All Objects  ----\n\n");
	}
	if(key == 'W'){
		if(!m_wallPos.empty())m_wallPos.clear();
		printf("\n---- Deleting All Walls  ----\n\n");
	}
	if(key == 'E'){
		if(!m_nodePos.empty())m_nodePos.clear();
		printf("\n---- Deleting All Nodes  ----\n\n");
	}
#ifdef BPD_DEBUGMODE
	if(key == '1'){ db_mode1 = !db_mode1; }
	if(key == '2'){ db_mode2 = !db_mode2; }
	if(key == '3'){ db_mode3 = !db_mode3; }
	if(key == '4'){ db_mode4 = !db_mode4; }
	if(key == '5'){ db_mode5 = !db_mode5; }
#endif
	if(key == 32){
		for(int i = 0; i < m_nodePos.size(); i++){
			if(m_nodePos[i].GetPos().distance(bpd::Point(m_mousePos.x, m_mousePos.y)) < 10){
				m_endNodeIndex = i;
				m_nodePos[i].type2 = AINode::END;
				break;
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
	/************************************************************************************************************/
	/************************************************************************************************************/
	/** Release Brushes */
	bpd::SafeRelease(&m_WhiteBrush);
	bpd::SafeRelease(&m_RedBrush);
	bpd::SafeRelease(&m_FadedRedBrush);
	bpd::SafeRelease(&m_GrayBrush);
	bpd::SafeRelease(&m_GreenBrush);
	bpd::SafeRelease(&m_NodeBrush);
	bpd::SafeRelease(&m_BlueBrush);
	bpd::SafeRelease(&m_PurpleBrush);
	/************************************************************************************************************/
	/************************************************************************************************************/
}
void MainWindow::OnDeviceResources(ID2D1HwndRenderTarget* rt){
	/************************************************************************************************************/
	/************************************************************************************************************/
	/** Create Brushes */
	rt->CreateSolidColorBrush( D2D1::ColorF(D2D1::ColorF::White), &m_WhiteBrush );
	rt->CreateSolidColorBrush( D2D1::ColorF(D2D1::ColorF::Red), &m_RedBrush );
	rt->CreateSolidColorBrush( D2D1::ColorF(D2D1::ColorF::Red, 0.3f), &m_FadedRedBrush );
	rt->CreateSolidColorBrush( D2D1::ColorF(D2D1::ColorF::Gray), &m_GrayBrush );
	rt->CreateSolidColorBrush( D2D1::ColorF(D2D1::ColorF::Green), &m_GreenBrush );
	rt->CreateSolidColorBrush( D2D1::ColorF(D2D1::ColorF::Gray), &m_NodeBrush );
	rt->CreateSolidColorBrush( D2D1::ColorF(D2D1::ColorF::BlueViolet), &m_BlueBrush );
	rt->CreateSolidColorBrush( D2D1::ColorF(D2D1::ColorF::Purple), &m_PurpleBrush );
	/************************************************************************************************************/
	/************************************************************************************************************/
	/** Set Opacity in Release Mode*/
#ifndef BPD_DEBUGMODE
	m_NodeBrush->SetOpacity(0.3f);
	m_PurpleBrush->SetOpacity(0.8f);
	m_GreenBrush->SetOpacity(0.3f);
	m_RedBrush->SetOpacity(0.3f);
#endif
}

bpd::LinkedList< AINode* > MainWindow::reconstructPath(AINode* cur) {
	if (cur->type2 != AINode::START) {
		m_path.push_back(cur);
		m_path.back().value->type = AINode::PATH;
		reconstructPath(cur->GetParent());
	} return m_path;
}

bpd::LinkedList<AINode*> MainWindow::CalcPath(int Start, int End) {
	StartNode = &m_nodePos.find(Start);
	EndNode = &m_nodePos.find(End);

	m_openNodes.clear();
	m_closedNodes.clear();

	for (int i = 0; i < m_nodePos.size(); i++) {
		m_nodePos[i].h = 0;
		m_nodePos[i].g = 0;
		m_nodePos[i].SetParent(nullptr);
		m_nodePos[i].type = AINode::NUL;
		m_nodePos[i].type2 == AINode::START ? AINode::START : AINode::NIL;
	}

	m_openNodes.push_back(StartNode);
	StartNode->type = AINode::OPEN;

	while (!m_openNodes.empty()) {

		AINode* CurrentNode = m_openNodes[0];
		for (int i = 0; i < m_openNodes.size(); i++) {
			if (m_openNodes[i]->f() < (*CurrentNode).f()) {
				CurrentNode = m_openNodes[i];
			}
		}

		m_openNodes.remove(m_openNodes.find_i(CurrentNode));
		m_closedNodes.push_back(CurrentNode);
		(*CurrentNode).type = AINode::CLOSED;

		if (CurrentNode == EndNode) {
			return reconstructPath(CurrentNode);
		}

		for (int i = 0; i < (*CurrentNode).m_edges.size(); i++) {
			if ((*CurrentNode).m_edges[i].Point2->type == AINode::CLOSED) continue;
			if ((*CurrentNode).m_edges[i].Point2->type != AINode::OPEN) {
				m_openNodes.push_back((*CurrentNode).m_edges[i].Point2);
				(*CurrentNode).m_edges[i].Point2->type = AINode::OPEN;

				int tentative_gScore = (*CurrentNode).g + (*CurrentNode).GetPos().distance((*CurrentNode).m_edges[i].Point2->GetPos());

				(*CurrentNode).m_edges[i].Point2->g = tentative_gScore;
				(*CurrentNode).m_edges[i].Point2->SetParent(CurrentNode);
				(*CurrentNode).m_edges[i].Point2->h = (*CurrentNode).m_edges[i].Point2->GetPos().distance(EndNode->GetPos());

			}
			else {
				int tentative_gScore = (*CurrentNode).g + (*CurrentNode).GetPos().distance((*CurrentNode).m_edges[i].Point2->GetPos());
				if (tentative_gScore <= (*CurrentNode).m_edges[i].Point2->g) {

					(*CurrentNode).m_edges[i].Point2->g = tentative_gScore;
					(*CurrentNode).m_edges[i].Point2->SetParent(CurrentNode);
					(*CurrentNode).m_edges[i].Point2->h = (*CurrentNode).m_edges[i].Point2->GetPos().distance(EndNode->GetPos());

				}
			}
		}
	}
	return bpd::LinkedList<AINode*>();
}

void MainWindow::linkNode(int index) {
	if (!m_nodePos.empty()) {
		int j = index;
		for (int i = 0; i < m_nodePos.size(); i++) {
			bool collided = false;
			if (m_nodePos[i].GetPos() == m_nodePos[j].GetPos()) continue;
			if (m_nodePos[i].GetPos().distance(m_nodePos[j].GetPos()) <= 200) {
				for (int k = 0; k < m_wallPos.size(); k++) {
					if (m_nodePos[i].GetPos().distance(m_wallPos[k].pos) <= 200) {
						bpd::Segment temp(m_nodePos[i].GetPos().x, m_nodePos[i].GetPos().y, m_nodePos[j].GetPos().x, m_nodePos[j].GetPos().y);
						if (temp.intersect(m_wallPos[k].seg1) == true ||
							temp.intersect(m_wallPos[k].seg2) == true ||
							temp.intersect(m_wallPos[k].seg3) == true ||
							temp.intersect(m_wallPos[k].seg4) == true) {
							collided = true;
						}
					}
				}
				if (collided) { continue; }
				/** Add edges to nodes */
				m_nodePos[i].m_edges.push_back(Edge(m_nodePos[i], m_nodePos[j]));
				m_nodePos[j].m_edges.push_back(Edge(m_nodePos[j], m_nodePos[i]));
			}
		}
	}
}


void MainWindow::OnPaint(ID2D1HwndRenderTarget* rt){
	m_timer.calcFPS();
	rt->SetTransform(D2D1::Matrix3x2F::Identity());
	rt->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	D2D1_SIZE_F rtSize = rt->GetSize();
	int width = static_cast<int>(rtSize.width);
	int height = static_cast<int>(rtSize.height);
	DrawGrid(rt, rtSize, width, height);

	/************************************************************************************************************/
	/************************************************************************************************************/
	/** Draw Walls */
	if(!m_wallPos.empty()){
		for(int i = 0; i < m_wallPos.size(); i++){
			D2D1_RECT_F wall = D2D1::Rect(
				m_wallPos[i].pos.x - 40.f, m_wallPos[i].pos.y - 40.f,
				m_wallPos[i].pos.x + 40.f, m_wallPos[i].pos.y + 40.f
			); rt->FillRectangle(&wall, m_WhiteBrush);
			/** Draw Wall Colliders */
			if(db_mode4){
				rt->DrawLine(
					D2D1::Point2F(m_wallPos[i].seg1.x, m_wallPos[i].seg1.y),
					D2D1::Point2F(m_wallPos[i].seg1.vecX, m_wallPos[i].seg1.vecY), m_RedBrush, 1.0f, 0
				);
				rt->DrawLine(
					D2D1::Point2F(m_wallPos[i].seg2.x, m_wallPos[i].seg2.y),
					D2D1::Point2F(m_wallPos[i].seg2.vecX, m_wallPos[i].seg2.vecY),
					m_RedBrush, 1.0f, 0
				);
				rt->DrawLine(
					D2D1::Point2F(m_wallPos[i].seg3.x, m_wallPos[i].seg3.y),
					D2D1::Point2F(m_wallPos[i].seg3.vecX, m_wallPos[i].seg3.vecY),
					m_RedBrush, 1.0f, 0
				);
				rt->DrawLine(
					D2D1::Point2F(m_wallPos[i].seg4.x, m_wallPos[i].seg4.y),
					D2D1::Point2F(m_wallPos[i].seg4.vecX, m_wallPos[i].seg4.vecY),
					m_RedBrush, 1.0f, 0
				);
			}
		}
	}
	if(!m_nodePos.empty()){
		for(int i = 0; i < m_nodePos.size(); i++){

			/** Draw Nodes */
			if (db_mode1) {
				D2D1_ELLIPSE node = D2D1::Ellipse(
					D2D1::Point2F(m_nodePos[i].GetPos().x, m_nodePos[i].GetPos().y),
					10.f, 10.f
				);
				if (db_mode3) {
					if (m_nodePos[i].GetParent() != nullptr) {
						bpd::Point thisnode = (m_nodePos[i].GetParent()->GetPos() - m_nodePos[i].GetPos()).normal();
						thisnode = thisnode * 50;
						rt->DrawLine(
							D2D1::Point2F(m_nodePos[i].GetPos().x, m_nodePos[i].GetPos().y),
							D2D1::Point2F(
								m_nodePos[i].GetPos().x + thisnode.x,
								m_nodePos[i].GetPos().y + thisnode.y
							),
							m_WhiteBrush, 3, 0
						);
					}
				}
				if (m_endNodeIndex != i) {
					switch (m_nodePos[i].type) {
					case AINode::PATH:
						rt->FillEllipse(&node, m_PurpleBrush); break;
					case AINode::CLOSED:
						rt->FillEllipse(&node, m_RedBrush); break;
					case AINode::OPEN:
						rt->FillEllipse(&node, m_GreenBrush); break;
					default:
						rt->FillEllipse(&node, m_GrayBrush); break;
					}
				}
				else { rt->FillEllipse(&node, m_BlueBrush); }
				if (m_lookatNodeIndex == i) rt->DrawEllipse(&node, m_RedBrush, 2);


			}
			/** Draw Edegs */
			if (db_mode2) {
				 if (m_lookatNodeIndex == -1) {
					for (int j = 0; j < m_nodePos[i].m_edges.size(); j++) {
						rt->DrawLine(
							D2D1::Point2F(m_nodePos[i].m_edges[j].Point1->GetPos().x, m_nodePos[i].m_edges[j].Point1->GetPos().y),
							D2D1::Point2F(m_nodePos[i].m_edges[j].Point2->GetPos().x, m_nodePos[i].m_edges[j].Point2->GetPos().y),
							m_GrayBrush, 1, 0
						);
					}
				}
			}
		}
	}
	if (db_mode2) {
		if (m_lookatNodeIndex != -1) {
			for (int j = 0; j < m_nodePos[m_lookatNodeIndex].m_edges.size(); j++) {
				rt->DrawLine(
					D2D1::Point2F(m_nodePos[m_lookatNodeIndex].m_edges[j].Point1->GetPos().x, m_nodePos[m_lookatNodeIndex].m_edges[j].Point1->GetPos().y),
					D2D1::Point2F(m_nodePos[m_lookatNodeIndex].m_edges[j].Point2->GetPos().x, m_nodePos[m_lookatNodeIndex].m_edges[j].Point2->GetPos().y),
					m_GrayBrush, 1, 0
				);
			}
		}
	}

	if(placingWall){
		/** Draw Temp Wall */
		D2D1_RECT_F tempWall = D2D1::Rect(
			m_mousePos.x - 40.f, m_mousePos.y - 40.f,
			m_mousePos.x + 40.f, m_mousePos.y + 40.f
		); rt->FillRectangle(&tempWall, m_FadedRedBrush);
	} else if(deletingObjects){
		/** Draw Temp Delete */
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
		/** Draw Temp Node */
		D2D1_ELLIPSE node = D2D1::Ellipse(
			D2D1::Point2F(m_mousePos.x, m_mousePos.y),
			10.f, 10.f
		); rt->FillEllipse(&node, m_FadedRedBrush);
	}
	{
		/** Draw Keys */
		const WCHAR m_GameText[] = L"---- A* Testing Area ----\n[Q] =\t\tClear All\n[W] =\t\tClear Walls\n[E] =\t\tClear Nodes\n[LShift] =\tDelete Mode\n[LCtrl] =\tWall Mode\n[LClick] =\tPlace Object\n[RClick] =\tMove Object\n[space] =\tSelect End Node";
		rt->DrawText(
			m_GameText,
			BPD_SIZEOF(m_GameText),
			m_pDebugTextFormat,
			D2D1::RectF(0, 0, 400, 200),
			m_WhiteBrush
		);
		/** Draw Debug Keys */
		const WCHAR m_debugText[] = L"---- Debug Binds ----\n[1] =\t\tShow Nodes\n[2] =\t\tShow Node Connectors";
		rt->DrawText(
			m_debugText,
			BPD_SIZEOF(m_debugText),
			m_pDebugTextFormat,
			D2D1::RectF(0,height, 400, height - 50),
			m_WhiteBrush
		);
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