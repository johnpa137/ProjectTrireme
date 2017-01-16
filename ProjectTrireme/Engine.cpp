#include "engine.h"

using namespace Trireme;

using std::fstream;
using std::string;
using std::cout;

Engine::Engine() : quit(false), frameTime(DEFAULT_FRAMETIME)
{	
	display = new Display();

	GameProperties::frameTime = &frameTime;
	GameProperties::windowWidth = display->getWidthAddress();
	GameProperties::windowHeight = display->getHeightAddress();
	
	// clears error cache of SDL
	SDL_ClearError();
	
	// initiates SDL and all of its components
	if (SDL_Init(SDL_INIT_EVERYTHING) < NULL)
		throw SDL_GetError();

	fstream defaultParamFile;
	
	defaultParamFile.open("engineParam.init", fstream::in);

	if (defaultParamFile.good())
	{
		ushort windowWidth, windowHeight;
		string windowName;

		defaultParamFile >> windowWidth;
		defaultParamFile >> windowHeight;
		defaultParamFile >> windowName;

		display->init(windowWidth, windowHeight, windowName.c_str());
	}
	else
	{
		defaultParamFile.close();
		defaultParamFile.open("engineParam.init", fstream::out);
		defaultParamFile << "640 480 Game";

		display->init(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "Game");
	}

	defaultParamFile.close();

	fontShader = new FontShader();
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

	// font->render_text("The quick brown fox jumps over the lazy <>.", 0.f, 0.f, glm::vec3(1.f, 0.5f, 0.f)); // just for testing

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
}