#pragma once
#pragma comment(lib, "d2d1")
#pragma comment(lib, "Dwrite")

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "../Biped/bpd/Exception.h"
#include "../Biped/bpd/IList.h"
#include "../Biped/bpd/ObjectPool.h"
#include "../Biped/bpd/bpdWinObjects.h"
#include "../Biped/bpd/Timer.h"

#include "type-window.h"

struct BpdWindow_bpd {
	char * test;
};