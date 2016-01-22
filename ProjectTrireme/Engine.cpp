#include "engine.h"

using namespace Trireme;

using std::fstream;
using std::string;
using std::cout;

Engine::Engine() : Quit(false), frameTime(DEFAULT_FRAMETIME)
{	
	GameProperties::frameTime = &frameTime;
	GameProperties::windowWidth = m_display.getWidthAddress();
	GameProperties::windowHeight = m_display.getHeightAddress();
	
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

		m_display.init(windowWidth, windowHeight, windowName.c_str());
	}
	else
	{
		defaultParamFile.close();
		defaultParamFile.open("engineParam.init", fstream::out);
		defaultParamFile << "640 480 Game";

		m_display.init(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "Game");
	}

	defaultParamFile.close();

	shdrFnt = new ShaderFont();
	shdrFnt->compile();
	shdrFnt->bind();

	scene = new Scene("Scenes/cube.fbx");
	font = new Font("Fonts/Blockstepped.ttf", shdrFnt);
}

void Engine::update()
{	
	m_display.clear();

	Uint32 frameStartTime = SDL_GetTicks();
	
	while (SDL_PollEvent(&m_event))
	{
		// checking if exit button was pressed
		if (m_event.type == SDL_QUIT)
			Quit = true;

		// put input handlers here

		m_display.input(m_event);
	}

	font->render_text("The quick brown fox jumps over the lazy <>.", 0.f, 0.f, glm::vec3(1.f, 0.5f, 0.f)); // just for testing

	scene->drawScene();

	m_display.update();

	Uint32 frameTime0 = SDL_GetTicks() - frameStartTime;

	if (float(frameTime0) < frameTime)
	{
		SDL_Delay(Uint32(frameTime - frameTime0));
	}
}

Engine::~Engine()
{
	SDL_Quit();
	delete shdrFnt;
	delete font;
	cout << "It's dead, Jim.\n";
}