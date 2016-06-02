#include "Shader.h"

#define ERROR_MAX 256

using namespace Trireme;

using std::string;

void ShaderProgram::attachShader(const std::string& sourceStrings, const uint16_t componentHandle)
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

void ShaderProgram::bind()const
{
	glUseProgram(handle);
}

void ShaderProgram::checkShaderError(const GLuint shaderHandle, const GLuint errorFlag, const bool isProgram,
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

void ShaderProgram::linkAndValidateShader(GLuint shaderHandle)
{
	glLinkProgram(shaderHandle);
	checkShaderError(shaderHandle, GL_LINK_STATUS, true, "Error: Program Linking Failed: ");
	glValidateProgram(shaderHandle);
	checkShaderError(shaderHandle, GL_VALIDATE_STATUS, true, "Error: Program is Invalid: ");
}

string ShaderProgram::getShaderSource(const char* filename)
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