#include "GraphicalEditor.h"

// DISCLAIMER: This is actually a strategy pattern
// The main difference is each strategy doesn't know about
// each other, but different states can change the current
// state of context

int main(int argc, char* args[]) {
	GraphicalEditor editor;
	std::cout << "Press 1 to choose brush tool\n";
	std::cout << "Press 2 to choose line tool\n";
	std::cout << "Press 3 to choose circle tool\n";
	std::cout << "Press space to clear screen\n";
	editor.run();
	return 0;
}