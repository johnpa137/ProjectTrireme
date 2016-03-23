#include "Engine.h"

int main(int argc, char** argv)
{	
	std::cout << "It's Alive!\n";

	Trireme::Engine engine;

	engine.run();
	
	return EXIT_SUCCESS;
}