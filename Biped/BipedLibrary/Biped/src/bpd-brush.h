// ################################################################## //
// ##							Brush							   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Sep 5 - AIE			   ## //
// ################################################################## //
#pragma once
_BPD_BEGIN
struct Brush {
	static HBRUSH Black;
	static HBRUSH White;
	static HBRUSH Gray;
	static HBRUSH Red;
	static HBRUSH Blue;
	static HBRUSH Green;
	static HBRUSH Yellow;
};

void ReleaseBrushs(Brush& obj);
_BPD_END