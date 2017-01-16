#include "Shader.h"

using namespace Trireme;

using std::string;

FontShader::FontShader()
{
	handle = glCreateProgram();

	for (ushort i = 0; i < UNIFORM_COUNT; ++i)
		uniforms[i] = NULL;

	components[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
	components[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);

	string shaderSources[SHADERTYPE_COUNT];

	shaderSources[VERTEX_SHADER] = getShaderSource("Shaders/fontVertShader.glsl");
	shaderSources[FRAGMENT_SHADER] = getShaderSource("Shaders/fontFragShader.glsl");

	attachShader(shaderSources[VERTEX_SHADER], components[VERTEX_SHADER]);
	attachShader(shaderSources[FRAGMENT_SHADER], components[FRAGMENT_SHADER]);

	compile();
}

void Shader::attachShader(const std::string& sourceStrings, const ushort componentHandle)
{
	const GLchar* shaderSourcesCStrings[1];
	GLint sourceCharCounts[1];

	shaderSourcesCStrings[0] = sourceStrings.c_str();
	sourceCharCounts[0] = sourceStrings.length();

	glShaderSource(componentHandle, 1, shaderSourcesCStrings, sourceCharCounts);

	glCompileShader(componentHandle);

	// this can throw an error
	checkShaderError(componentHandle, GL_COMPILE_STATUS, GL_FALSE, "Error: Shader Compilation Failed: ");

	glAttachShader(handle, componentHandle);
}

void FontShader::compile()
{
	glBindAttribLocation(handle, VERTEX, "vertex");

	linkAndValidateShader(handle);

	uniforms[TEXT_COLOR] = glGetUniformLocation(handle, "text_color");
}

void FontShader::bind()const
{
	glUseProgram(handle);
}

FontShader::~FontShader()
{
	for (ushort i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		glDetachShader(handle, components[i]);
		glDeleteShader(components[i]);
	}

	glDeleteProgram(handle);
}

void Shader::checkShaderError(const GLuint shaderHandle, const GLuint errorFlag, const bool isProgram,
	const string& errorMessage)
{
	GLint success = 0;
	GLchar error[ERROR_MAX] = { 0 };

	// checks if checking for error on a shader program handle or shader component handle
	if (isProgram)
		// gets info for shader program, and assigns a positive value to success if successful
		glGetProgramiv(shaderHandle, errorFlag, &success);
	else
		// gets info for shader component, and assigns a positive value to success if successful
		glGetShaderiv(shaderHandle, errorFlag, &success);

	// checks if success is not false
	if (!success)
	{
		if (isProgram)
			// gets error mess
			glGetProgramInfoLog(shaderHandle, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shaderHandle, sizeof(error), NULL, error);

		// prints errormessage to console
		throw (errorMessage + ": '" + error + "'");
	}
}

void Shader::linkAndValidateShader(GLuint shaderHandle)
{
	glLinkProgram(shaderHandle);
	checkShaderError(shaderHandle, GL_LINK_STATUS, true, "Error: Program Linking Failed: ");
	glValidateProgram(shaderHandle);
	checkShaderError(shaderHandle, GL_VALIDATE_STATUS, true, "Error: Program is Invalid: ");
}

string Shader::getShaderSource(const char* filename)
{
	std::ifstream file;

	file.open(filename, std::fstream::in);

	string line;
	string source;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			source.append(line + "\n");
		}
	}

	return source;
}