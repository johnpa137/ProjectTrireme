#include "engine.h"

#define DEFAULT_SCREEN_WIDTH 640

#define DEFAULT_SCREEN_HEIGHT 480

#define DEFAULT_FRAMETIME 1000.f / 60.f

#define DEFAULT_FRAMERATE 60.f

#define DEFAULT_WINDOW_TITLE "Trireme Engine"

using namespace Trireme;

using std::fstream;
using std::string;
using std::cout;

Engine::Engine() : quit(false), frameTime(DEFAULT_FRAMETIME)
{	
	display = new Display();

	EngineProperties::frameTime = &frameTime;
	EngineProperties::windowWidth = display->getWidthAddress();
	EngineProperties::windowHeight = display->getHeightAddress();
	
	// clears error cache of SDL
	SDL_ClearError();
	
	// initiates SDL and all of its components
	if (SDL_Init(SDL_INIT_EVERYTHING) < NULL)
		throw SDL_GetError();

	setup();
	try{
		fontShader = new FontShader();
	}
	catch (std::string err)
	{
		cout << err;
	}
	
	fontShader->bind();

	font = new Font("Fonts/Blockstepped.ttf", fontShader);
}

void Engine::update()
{	
	display->clear();

	Uint32 frameStartTime = SDL_GetTicks();
	
	while (SDL_PollEvent(&sdl_event))
	{
		// checking if exit button was pressed
		if (sdl_event.type == SDL_QUIT)
		{
			quit = true; 
			return;
		}
			
		// put input handlers here
		display->input(sdl_event);
	}

	display->update();

	step(SDL_GetTicks() - frameStartTime);
}

void Engine::step(const Uint32 frameLength)
{
	if (float(frameLength) < frameTime)
	{
		SDL_Delay(Uint32(frameTime - frameLength));
	}
}

void Engine::setup()
{
	display->init(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, DEFAULT_WINDOW_TITLE);
}

void Engine::run()
{
	while (!quit)
		update();
}

Engine::~Engine()
{
	delete font;
	font = nullptr;
	delete fontShader;
	fontShader = nullptr;
	delete display;
	display = nullptr;
	SDL_Quit();
	cout << "It's dead, Jim.\n";
	int i = 0;
}