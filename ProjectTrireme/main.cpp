#include "Engine.h"

int main(int argc, char** argv)
{	
	std::cout << "It's Alive!\n";

	{
		Trireme::Engine engine;

		while (!engine.Quit)
			engine.update();
	}
	
	return EXIT_SUCCESS;
}