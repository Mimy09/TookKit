#ifndef _DXDEF_H_
#define _DXDEF_H_
#include "bpddef.h"

BPD_BEGIN
static bool fullScreen = false;
const bool vsyncEnabled = true;
const float screenDepth = 1000.0f;
const float screenNear = 0.1f;
BPD_END
#define FULL_SCREEN bpd::fullScreen
#define VSYNC_ENABLED bpd::vsyncEnabled
#define SCREEN_DEPTH bpd::screenDepth
#define SCREEN_NEAR bpd::screenNear

#endif // !_DXDEF_H_