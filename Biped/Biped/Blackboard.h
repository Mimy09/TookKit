#pragma once
/************************************************
#################################################
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	---- THIS FILE HAS AN ERROR SOMEWHERE ----
	  ---- WILL CREATE OVER 200+ ERRORS ----
			  ---- DO NOT USE ----

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#################################################
************************************************/
#pragma error("USING FILE MARKED AS (((DO NOT USE)))")


//************************************
// Includes
#include "bpd/Core/bpddef.h"
//************************************

typedef unsigned int BLACKBOARD_ID;

template<typename _Type>
class Blackboard {
public:
	typedef _Type t_value;
	typedef _Type* pt_value;
	typedef _Type** ppt_value;
	typedef _Type*** pppt_value; // <--- Maybe someting to do with a triple pointer --->
	typedef int * pt_id;
public:
	Blackboard(){
		if(m_bpdblackboard == nullptr) {
			m_bpdblackboard = new ppt_value[20];
			for(int i = 0; i < 20; i++) {
				m_bpdblackboard[i] = nullptr;
			}
		}
	}
	~Blackboard(){}

	BLACKBOARD_ID createNewBlackboard() {
		if(m_bpdblackboard_id == nullptr) { m_bpdblackboard_id = new int(1); } return (*m_bpdblackboard_id)++;
	}
	bool post(t_value msg, BLACKBOARD_ID id = 0) {
		t_value * p_msg = new t_value(msg);
		if(m_bpdblackboard[id] == nullptr) {
			m_bpdblackboard[id] = new pt_value[50];
			for(int i = 0; i < 50; i++) {
				m_bpdblackboard[id][i] = nullptr;
			}
		}

		for(int i = 0; i < 50; i++) {
			if(m_bpdblackboard[id][i] == nullptr) {
				m_bpdblackboard[id][i] = &p_msg;
				return true;
			}
		} return false;
	}
	ppt_value getPosts(BLACKBOARD_ID id = 0) {
		if(m_bpdblackboard == nullptr || m_bpdblackboard[id] == nullptr) {
			return nullptr;
		}return m_bpdblackboard[id];
	}
	void clear(BLACKBOARD_ID id = 0) {
		BPD_SAFE_ARRAY_DELETE(m_bpdblackboard[id]);
		if(m_bpdblackboard[id] == nullptr) {
			m_bpdblackboard[id] = new pt_value[50];
			for(int i = 0; i < 50; i++) {
				m_bpdblackboard[id][i] = nullptr;
			}
		}
	}
	void remove(t_value msg, BLACKBOARD_ID id = 0) {
		if(m_bpdblackboard[id] == nullptr) return;
		for(int i = 0; i < 50; i++) {
			if(*m_bpdblackboard[id][i] == msg) {
				m_bpdblackboard[id][i] = nullptr;
			}
		}
	}
	void clearAdd() { Release(); }

	void Release() { // <--- Maybe someting to do with deleting a triple pointer --->
		BPD_SAFE_ARRAY_DELETE(m_id);
		for(int i = 0; i < 20; i++) { 
			for(int ii = 0; ii < 50; ii++) {
				BPD_SAFE_DELETE(m_bpdblackboard[i][ii]);
			} BPD_SAFE_ARRAY_DELETE(m_bpdblackboard[i]);
		} BPD_SAFE_ARRAY_DELETE(m_bpdblackboard);
	}

private:
	static pt_id m_bpdblackboard_id;
	static pppt_value m_bpdblackboard; // <--- Maybe someting to do with static triple pointer in a template class --->
};
BPD_TEMPLATE_CLASS BPD_TEMPLATE(Blackboard)::pt_id Blackboard<BPD_TEMPLATE_TYPE>::m_bpdblackboard_id = nullptr;
BPD_TEMPLATE_CLASS BPD_TEMPLATE(Blackboard)::pppt_value Blackboard<BPD_TEMPLATE_TYPE>::m_bpdblackboard = nullptr;