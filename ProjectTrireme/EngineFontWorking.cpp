#include "engine.h"

using namespace Trireme;

using std::fstream;
using std::string;
using std::cout;

Engine::Engine() : Quit(false)
{
	// clears error cache of SDL
	SDL_ClearError();
	
	// initiates SDL and all of its components
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw SDL_GetError();

	fstream defaultParamFile;
	
	defaultParamFile.open("engineParam.init", fstream::in);

	if (defaultParamFile.good())
	{
		unsigned short windowWidth, windowHeight;
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

		m_display.init(640, 480, "Game");
	}

	sx = 2.f/640;
	sy = 2.f/480;

	defaultParamFile.close();

	try{
		shaderFont = new ShaderFont();
		shaderFont->compile();
		shaderFont->bind();
	}
	catch (std::string& error)
	{
		std::cout << error;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	FT_Init_FreeType(&library);

	FT_New_Face(library, "Fonts/FreeSans.ttf", 0, &face);

	FT_Set_Pixel_Sizes(face, 0, 48);

	FT_Load_Char(face, 'L', FT_LOAD_RENDER);

	g = face->glyph;

	//uniform_tex = glGetUniformLocation(shaderFont->handle, "tex");
}

void Engine::update()
{	
	m_display.clear();
	
	while (SDL_PollEvent(&m_event))
	{
		// checking if exit button was pressed
		if (m_event.type == SDL_QUIT)
			Quit = true;
	}

	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	//glUniform1i(uniform_tex, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glEnableVertexAttribArray(Shader::Attribs::VERTEX);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(Shader::Attribs::VERTEX, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		g->bitmap.width,
		g->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		g->bitmap.buffer
		);

	float x2 = g->bitmap_left * sx;
	float y2 = -g->bitmap_top * sy;
	float w = g->bitmap.width * sx;
	float h = g->bitmap.rows * sy;

	std::vector<vec4> box;
	box.push_back(vec4(x2, -y2, 0.f, 0.f));
	box.push_back(vec4(x2 + w, -y2, 1.f, 0.f));
	box.push_back(vec4(x2, -y2 - h, 0.f, 1.f));
	box.push_back(vec4(x2 + w, -y2 - h, 1.f, 1.f));

	glBufferData(GL_ARRAY_BUFFER, sizeof(box[0]) * box.size(), &box[0], GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	m_display.update();
}

Engine::~Engine()
{
	SDL_Quit();
	delete shaderFont;
	FT_Done_Face(face);
	FT_Done_FreeType(library);
	cout << "It's dead, Jim.\n";
}