#include "Main.h"
#include "Biped/src/bpd-math.h"

int main() {
	FOOBAR* window = new FOOBAR();

	bpd::Window win;
	bpd::WindowInfo info;
	info.ClassName = "TEST_CLASS_NAME";
	info.TitleName = "Title";
	info.FullScreen = false;

	Maths::Vector<int> test = { {0, 1, 2, 3} };
	test.operator() <Maths::_X_<int>> ();


	if(bpd::WindowCreate(win, info) == BPD_RESULT::SUCCESS) {
		bpd::bind(win);
		bpd::linkClass(window);

		bpd::WindowShow(win);
		bpd::WindowRun(win);
	}

	return 0;
}