// engine.h
// file contains the declarations for functions concerning the starting of the engine, loading of game files, and updating the game and engine data

#pragma once

#include <iostream>
#include <fstream>
#include "constdef.h"
#include "Display.h"
#include "Shader.h"
#include "Font.h"
#include "SDL2\SDL.h"
#include "GL\glew.h"

#include <vector>

namespace Trireme
{
	// 
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
		ShaderFont* shaderFont;
		FT_Library library;
		FT_Face face;
		FT_GlyphSlot g;
		float sx, sy;
		GLint uniform_tex;
		SDL_Event m_event;
	};
}