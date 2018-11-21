//-------------------------------------------------------------------------------------------------
// #pragma warning(disable:4996)

#ifndef TRIREME_DISPLAY_H
#define TRIREME_DISPLAY_H

#include "SDL2\SDL.h"
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "constdef.h"

#include <string>

namespace Trireme
{
	// class that manipulates and updates the window and openGL context
	class Display
	{
	public:
		// default constructor
		// creates display object and sets its values to NULL
		Display();

		// initializes window and glContext with param values
		// throws:
		// * SDL_Video was not initialized
		// * A gl attribute failed to be set...
		// * Game window failed to be created
		// * OpenGL context failed to be created
		void init(const ushort screenWidth, const ushort screenHeight, const char* windowName);

		// swaps frame buffers each frame to update screen
		void update();

		// clears display
		void clear();

		// object event handling
		void input(SDL_Event& e);

		// sets display to fullScreen
		// flags = {SDL_WINDOW_FULLSCREEN, SDL_WINDOW_FULLSCREEN_DESKTOP, 0}
		// SDL_WINDOW_FULLSCREEN is for true fullscreen video mode
		// SDL_WINDOW_FULLSCREEN_DESKTOP is for fullscreen at window resolution
		// 0 is for windowed mode
		// throws:
		// * could net set to fullscreen
		void setFullScreen(const Uint32 flag);

		// sets window size to specified parameters
		void setWindowSize(const ushort width, const ushort height);

		// sets the title that shows on the top bar of the window
		void setWindowName(const char* windowName);

		// sets clear color
		void setClearColor(const float r, const float g, const float b, const float a)const;

		ushort* getWidthAddress() { return &m_width; }
		ushort* getHeightAddress() { return &m_height; }

		//destructor, destroys window and openGL context
		~Display();

	private:
		// pointer to the window we're using
		SDL_Window* m_window;
		// the openGL context this program is using
		SDL_GLContext m_context;

		// window dimensions
		ushort m_width;
		ushort m_height;
	};
}

#endif