#include "RectShader.h"

using namespace Trireme;

using std::string;

string * RectShader::shaderSources = nullptr;

void RectShader::fillShaderSources()
{
	shaderSources = new string[TOTAL_NUMBEROF_SHADER_SOURCES];

	shaderSources[COLOR_RECT_VS] = getShaderSource("Shaders/ColorRectShader.vs");
	shaderSources[IMAGE_RECT_VS] = getShaderSource("Shaders/ImageRectShader.vs");
	shaderSources[COLOR_RECT_GS] = getShaderSource("Shaders/ColorRectShader.gs");
	shaderSources[IMAGE_RECT_GS] = getShaderSource("Shaders/ImageRectShader.gs");
	shaderSources[GRADIENT_RECT_GS] = getShaderSource("Shaders/GradientRectShader.gs");
	shaderSources[BORDER_RECT_GS] = getShaderSource("Shaders/BorderRectShader.gs");
	shaderSources[COLOR_RECT_FS] = getShaderSource("Shaders/ColorRectShader.fs");
	shaderSources[IMAGE_RECT_FS] = getShaderSource("Shaders/ImageRectShader.fs");
	shaderSources[LINEAR_GRADIENT_RECT_FS] = getShaderSource("Shaders/LinearGradientRectShader.fs");
	shaderSources[RADIAL_GRADIENT_RECT_FS] = getShaderSource("Shaders/RadialGradientRectShader.fs");
	shaderSources[BORDER_RECT_FS] = getShaderSource("Shaders/BorderRectShader.fs");
}

void RectShader::clearShaderSources()
{
	delete[] shaderSources;
}

ColorRectShader::ColorRectShader()
{
	handle = glCreateProgram();

	components[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
	components[GEOMETRY_SHADER] = glCreateShader(GL_GEOMETRY_SHADER);
	components[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);

	string shaderSources[SHADERTYPE_COUNT];

	// shaderSources[VERTEX_SHADER] = getShaderSource("Shaders/ColorRectShader.vs");
	// shaderSources[GEOMETRY_SHADER] = getShaderSource("Shaders/ColorRectShader.gs");
	// shaderSources[FRAGMENT_SHADER] = getShaderSource("Shaders/ColorRectShader.fs");

	attachShader(shaderSources[COLOR_RECT_VS], components[VERTEX_SHADER]);
	attachShader(shaderSources[COLOR_RECT_GS], components[GEOMETRY_SHADER]);
	attachShader(shaderSources[COLOR_RECT_FS], components[FRAGMENT_SHADER]);

	compile();
}

void ColorRectShader::compile()
{
	glBindAttribLocation(handle, VERTEX, "InVertex");

	linkAndValidateShader(handle);
}

ColorRectShader::~ColorRectShader()
{
	for (uint16_t i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		glDetachShader(handle, components[i]);
		glDeleteShader(components[i]);
	}

	glDeleteProgram(handle);
}

ImageRectShader::ImageRectShader()
{
	handle = glCreateProgram();

	components[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
	components[GEOMETRY_SHADER] = glCreateShader(GL_GEOMETRY_SHADER);
	components[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);

	string shaderSources[SHADERTYPE_COUNT];

	attachShader(shaderSources[IMAGE_RECT_VS], components[VERTEX_SHADER]);
	attachShader(shaderSources[IMAGE_RECT_GS], components[GEOMETRY_SHADER]);
	attachShader(shaderSources[IMAGE_RECT_FS], components[FRAGMENT_SHADER]);

	compile();
}

void ImageRectShader::compile()
{
	glBindAttribLocation(handle, VERTEX, "InVertex");
	glBindAttribLocation(handle, UV, "InUVRect");

	linkAndValidateShader(handle);
}

ImageRectShader::~ImageRectShader()
{
	for (uint16_t i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		glDetachShader(handle, components[i]);
		glDeleteShader(components[i]);
	}

	glDeleteProgram(handle);
}

LinearGradientRectShader::LinearGradientRectShader()
{
	handle = glCreateProgram();

	components[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
	components[GEOMETRY_SHADER] = glCreateShader(GL_GEOMETRY_SHADER);
	components[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);

	string shaderSources[SHADERTYPE_COUNT];

	attachShader(shaderSources[COLOR_RECT_VS], components[VERTEX_SHADER]);
	attachShader(shaderSources[GRADIENT_RECT_GS], components[GEOMETRY_SHADER]);
	attachShader(shaderSources[LINEAR_GRADIENT_RECT_FS], components[FRAGMENT_SHADER]);

	compile();
}

LinearGradientRectShader::~LinearGradientRectShader()
{
	for (uint16_t i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		glDetachShader(handle, components[i]);
		glDeleteShader(components[i]);
	}

	glDeleteProgram(handle);
}

RadialGradientRectShader::RadialGradientRectShader()
{
	handle = glCreateProgram();

	components[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
	components[GEOMETRY_SHADER] = glCreateShader(GL_GEOMETRY_SHADER);
	components[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);

	string shaderSources[SHADERTYPE_COUNT];

	attachShader(shaderSources[COLOR_RECT_VS], components[VERTEX_SHADER]);
	attachShader(shaderSources[GRADIENT_RECT_GS], components[GEOMETRY_SHADER]);
	attachShader(shaderSources[RADIAL_GRADIENT_RECT_FS], components[FRAGMENT_SHADER]);

	compile();
}

RadialGradientRectShader::~RadialGradientRectShader()
{
	for (uint16_t i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		glDetachShader(handle, components[i]);
		glDeleteShader(components[i]);
	}

	glDeleteProgram(handle);
}

BorderRectShader::BorderRectShader()
{
	handle = glCreateProgram();

	components[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
	components[GEOMETRY_SHADER] = glCreateShader(GL_GEOMETRY_SHADER);
	components[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);

	string shaderSources[SHADERTYPE_COUNT];

	attachShader(shaderSources[COLOR_RECT_VS], components[VERTEX_SHADER]);
	attachShader(shaderSources[BORDER_RECT_GS], components[GEOMETRY_SHADER]);
	attachShader(shaderSources[BORDER_RECT_FS], components[FRAGMENT_SHADER]);

	compile();
}

BorderRectShader::~BorderRectShader()
{
	for (uint16_t i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		glDetachShader(handle, components[i]);
		glDeleteShader(components[i]);
	}

	glDeleteProgram(handle);
}