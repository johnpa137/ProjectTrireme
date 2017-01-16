//-------------------------------------------------------------------------------------------------
#include "Display.h"

using namespace Trireme;

Display::Display()
{
	window = NULL;
	context = NULL;
}

void Display::init(const ushort screenWidth, const ushort screenHeight, const char* windowName)
{
	// display needs sdl's video subsystem, checks if it was enabled, sdl_wasinit returns a Uint32
	if (SDL_WasInit(SDL_INIT_VIDEO) != SDL_INIT_VIDEO)
		throw "SDL_Video was not initialized for Display class.";

	width = screenWidth;
	height = screenHeight;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);

	// all of these return a zero or negative number on error
	// size of each color channel for the frame buffer, essentialy amount of data for each pixel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// sum of numbers above, basically number of bits each pixel requires
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	// basically how accurate we allow our depth buffer to be, 1.0f in the depth buffer is equal 
	// to our clipping distance
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	// 1 for true, 0 for false, a frame buffer is essentially an image to display on screen,
	// double buffer means we draw on two images, one to draw on and one to display and we switch
	// between them each frame
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// checks if sdl encountered an error, by checking if SDL_GetError() returns an empty string
	if (SDL_GetError()[0] != 0)
	{
		std::string errorMsg = "A GL Attribute failed to be set.";
		throw (errorMsg + SDL_GetError()).c_str();
	}

	// creates a window that is able to be set with an openGL context
	window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	// checks if window was actually created
	if (window == NULL)
		throw "Game window failed to be created.";

	// creates an openGL context for the window, using the attributes we set earlier
	context = SDL_GL_CreateContext(window);

	// more error checking there's going to be a lot of that in the initial setup
	if (context == NULL)
		throw "OpenGL context failed to be created.";

	// initializes GLEW and checks if it initialized correctly
	if (glewInit() != GLEW_OK)
		throw "GLEW failed to initialize.";

	// clear color is set default to black in rgba format
	glClearColor(0.15f, 0.15f, 0.15f, 1.f);

	// specifies which faces are back and front, clockwise
	glFrontFace(GL_CW);
	// specifies which faces are culled
	glCullFace(GL_BACK);
	// enables face culling
	glEnable(GL_CULL_FACE);
	// depth test is enabled, culling vertices that are too distant, according to later specified 
	// clip distance
	glDisable(GL_DEPTH_TEST);
	// prevents objects that are partially within ranged from being clipped
	glEnable(GL_DEPTH_CLAMP);
	// enables blending of colors
	glEnable(GL_BLEND);
	// defines the type of blending opengl does
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Display::update()
{
	SDL_GL_SwapWindow(window);
}

void Display::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::input(SDL_Event& e)
{
	if (e.type == SDL_WINDOWEVENT)
		if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			int w, h;
			
			SDL_GetWindowSize(window, &w, &h);

			width = w;
			height = h;

			glViewport(0, 0, w, h);
		}
}

void Display::setFullScreen(Uint32 flag)
{
	if (SDL_SetWindowFullscreen(window, flag) != 0)
		throw "could not set fullscreen";
}

void Display::setWindowSize(const ushort width, const ushort height)
{
	SDL_SetWindowSize(window, width, height);

	this->width = width;
	this->height = height;
}

void Display::setWindowName(const char* windowName)
{
	SDL_SetWindowTitle(window, windowName);
}

void Display::setClearColor(const float r, const float g, const float b, const float a)
{
	glClearColor(r, g, b, a);
}

Display::~Display()
{
	SDL_GL_DeleteContext(context);
	context = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
}