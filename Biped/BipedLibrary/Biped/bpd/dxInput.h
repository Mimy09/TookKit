#ifndef _DXINPUT_H_
#define _DXINPUT_H_
#define DXINPUT_KEYLENGTH 256
#include "Core\bpddef.h"

BPD_BEGIN
class dxInput {
public:
	dxInput();
	dxInput(const dxInput&);
	~dxInput();

	void initalize();
	void keyDown(unsigned int);
	void keyUp(unsigned int);

	bool isKeyDown(unsigned int);
private:
	bool m_keys[DXINPUT_KEYLENGTH];
};
BPD_END
#endif // !_DXINPUT_H_