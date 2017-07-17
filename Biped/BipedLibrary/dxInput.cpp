#include "Biped\bpd\dxInput.h"
BPD_BEGIN

dxInput::dxInput() {}
dxInput::dxInput(const dxInput& other) {}
dxInput::~dxInput() {}

void dxInput::initalize() {
	for (int i = 0; i < DXINPUT_KEYLENGTH; i++) {
		m_keys[i] = false;
	} return;
}

void dxInput::keyDown(size_type input) {
	m_keys[input] = true;
	return;
}

void dxInput::keyUp(size_type input) {
	m_keys[input] = false;
	return;
}

bool dxInput::isKeyDown(size_type input) {
	return m_keys[input];
}

BPD_END