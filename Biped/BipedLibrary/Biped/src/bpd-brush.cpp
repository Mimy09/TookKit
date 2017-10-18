#include "../bpd-def.h"
_BPD_BEGIN
HBRUSH Brush::Black = CreateSolidBrush(RGB(0, 0, 0));
HBRUSH Brush::White = CreateSolidBrush(RGB(255, 255, 255));
HBRUSH Brush::Gray = CreateSolidBrush(RGB(126, 122, 126));

HBRUSH Brush::Red = CreateSolidBrush(RGB(255, 0, 0));
HBRUSH Brush::Blue = CreateSolidBrush(RGB(0, 0, 255));
HBRUSH Brush::Green = CreateSolidBrush(RGB(0, 255, 0));
HBRUSH Brush::Yellow = CreateSolidBrush(RGB(255, 255, 0));

void ReleaseBrushs(Brush& obj) {
	DeleteObject(obj.Black);
	DeleteObject(obj.White);
	DeleteObject(obj.Gray);
	DeleteObject(obj.Red);
	DeleteObject(obj.Blue);
	DeleteObject(obj.Green);
	DeleteObject(obj.Yellow);
}
_BPD_END