#include <mw/window.h>

using namespace std;
using namespace mw;

class TestWindow : public Window {
public:
	TestWindow() : Window(300,300,true,"Test") {
	}
};

int main(int argc, char** argv) {
	TestWindow game;
	game.startLoop();

    return 0;
}
