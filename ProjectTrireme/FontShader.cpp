#include "FontShader.h"

using namespace Trireme;

using std::string;

FontShader::FontShader()
{
	handle = glCreateProgram();

	for (uint16_t i = 0; i < UNIFORM_COUNT; ++i)
		uniforms[i] = NULL;

	components[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
	components[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);

	string shaderSources[SHADERTYPE_COUNT];

	shaderSources[VERTEX_SHADER] = getShaderSource("Shaders/fontShader.vs");
	shaderSources[FRAGMENT_SHADER] = getShaderSource("Shaders/fontShader.fs");

	attachShader(shaderSources[VERTEX_SHADER], components[VERTEX_SHADER]);
	attachShader(shaderSources[FRAGMENT_SHADER], components[FRAGMENT_SHADER]);

	compile();
}

void FontShader::compile()
{
	glBindAttribLocation(handle, VERTEX, "vertex");

	linkAndValidateShader(handle);

	uniforms[TEXT_COLOR] = glGetUniformLocation(handle, "text_color");
}

FontShader::~FontShader()
{
	for (uint16_t i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		glDetachShader(handle, components[i]);
		glDeleteShader(components[i]);
	}

	glDeleteProgram(handle);
}