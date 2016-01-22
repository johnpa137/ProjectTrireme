// engine.h
// file contains the declarations for functions concerning the starting of the engine, loading of game files, and updating the game and engine data

#pragma once

#include <iostream>
#include <fstream>
#include "Display.h"
#include "Font.h"
#include "ObjectFbx.h"

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

		// if set true program quits
		bool Quit;

		// updates the running components of the engine
		void update();

		// deallocates memory of objects running in the engine
		~Engine();
	private:
		Display m_display;
		Font* font; // * just for testing
		ShaderFont* shdrFnt; // * just for testing
		Scene* scene;
		SDL_Event m_event;
		float frameTime;
	};
}