// engine.h
// file contains the declarations for functions concerning the starting of the engine, loading of game files, and updating the game and engine data

#ifndef TRIREME_ENGINE_H
#define TRIREME_ENGINE_H

#include <iostream>
#include <fstream>
#include "Display.h"
#include "Font.h"

namespace Trireme
{
	// wrapper class for the program
	class Engine
	{
	public:
		// this function initiates the engines components and dependencies such sdl, glew, sdl_image, and freetype
		// throws:
		// * sdl_geterror()
		Engine();

		// function for main
		void run();

		// deallocates memory of objects running in the engine
		~Engine();
	private:
		Display* display;
		Font* font; // * just for testing
		FontShader* fontShader; // * just for testing
		SDL_Event sdl_event; // event seems to show up as a keyword
		float frameTime;
		// if set true program quits
		bool quit;

		// updates the running components of the engine
		void update();
		// syncs framerate
		void step(const Uint32 frameLength);
	};
}

#endif