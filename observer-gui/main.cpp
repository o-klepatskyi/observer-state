#include "ClockApp.h"
#include <iostream>

int main(int argc, char* args[]) {
	ClockApp app;

	std::cout << "Press 1 to attach/detach digital clock\n"
		<< "Press 2 to attach/detach analog clock\n";
	app.run();
	return 0;
}
