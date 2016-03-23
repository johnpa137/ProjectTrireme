#include "Shader.h"

using namespace Trireme;

using std::string;

ShaderGUI::ShaderGUI()
{
	handle = glCreateProgram();

	for (ushort i = 0; i < UNIFORM_COUNT; ++i)
		uniforms[i] = NULL;

	m_components[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
	m_components[GEOMETRY_SHADER] = glCreateShader(GL_GEOMETRY_SHADER);
	m_components[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);

	string shaderSources[SHADERTYPE_COUNT];

	shaderSources[VERTEX_SHADER] = getShaderSource("Shaders/guiVertShader.glsl");
	shaderSources[GEOMETRY_SHADER] = getShaderSource("Shaders/guiGeomShader.glsl");
	shaderSources[FRAGMENT_SHADER] = getShaderSource("Shaders/guiFragShader.glsl");
	
	for (ushort i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		const GLchar* shaderSourcesCStrings[1];
		GLint sourceCharCounts[1];

		shaderSourcesCStrings[0] = shaderSources[i].c_str();
		sourceCharCounts[0] = shaderSources[i].length();

		glShaderSource(m_components[i], 1, shaderSourcesCStrings, sourceCharCounts);

		glCompileShader(m_components[i]);

		// this can throw an error
		checkShaderError(m_components[i], GL_COMPILE_STATUS, GL_FALSE, "Error: Shader Compilation Failed: ");

		glAttachShader(handle, m_components[i]);
	}
}

void ShaderGUI::compile()
{
	glBindAttribLocation(handle, VERTEX, "vertex");
	glBindAttribLocation(handle, HEIGHTANDWIDTH, "heightAndWidth");
	//glBindAttribLocation(handle, UV, "uv");
	//glBindAttribLocation(handle, UVDIMENSIONS, "uvDim");

	linkAndValidateShader(handle);
}

void ShaderGUI::bind()const
{
	glUseProgram(handle);
}

ShaderGUI::~ShaderGUI()
{
	for (ushort i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		glDetachShader(handle, m_components[i]);
		glDeleteShader(m_components[i]);
	}

	glDeleteProgram(handle);
}

ShaderFont::ShaderFont()
{
	handle = glCreateProgram();

	for (ushort i = 0; i < UNIFORM_COUNT; ++i)
		uniforms[i] = NULL;

	m_components[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
	m_components[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);

	string shaderSources[SHADERTYPE_COUNT];

	shaderSources[VERTEX_SHADER] = getShaderSource("Shaders/fontVertShader.glsl");
	shaderSources[FRAGMENT_SHADER] = getShaderSource("Shaders/fontFragShader.glsl");

	for (ushort i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		const GLchar* shaderSourcesCStrings[1];
		GLint sourceCharCounts[1];

		shaderSourcesCStrings[0] = shaderSources[i].c_str();
		sourceCharCounts[0] = shaderSources[i].length();

		glShaderSource(m_components[i], 1, shaderSourcesCStrings, sourceCharCounts);

		glCompileShader(m_components[i]);

		// this can throw an error
		checkShaderError(m_components[i], GL_COMPILE_STATUS, GL_FALSE, "Error: Shader Compilation Failed: ");

		glAttachShader(handle, m_components[i]);
	}
}

void ShaderFont::compile()
{
	glBindAttribLocation(handle, VERTEX, "vertex");

	linkAndValidateShader(handle);

	uniforms[TEXT_COLOR] = glGetUniformLocation(handle, "text_color");
}

void ShaderFont::bind()const
{
	glUseProgram(handle);
}

ShaderFont::~ShaderFont()
{
	for (ushort i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		glDetachShader(handle, m_components[i]);
		glDeleteShader(m_components[i]);
	}

	glDeleteProgram(handle);
}

ShaderSimple::ShaderSimple()
{
	handle = glCreateProgram();

	for (ushort i = 0; i < UNIFORM_COUNT; ++i)
		uniforms[i] = NULL;

	m_components[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
	m_components[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);

	string shaderSources[SHADERTYPE_COUNT];

	shaderSources[VERTEX_SHADER] = getShaderSource("Shaders/simpVertShader.glsl");
	shaderSources[FRAGMENT_SHADER] = getShaderSource("Shaders/simpFragShader.glsl");

	for (ushort i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		const GLchar* shaderSourcesCStrings[1];
		GLint sourceCharCounts[1];

		shaderSourcesCStrings[0] = shaderSources[i].c_str();
		sourceCharCounts[0] = shaderSources[i].length();

		glShaderSource(m_components[i], 1, shaderSourcesCStrings, sourceCharCounts);

		glCompileShader(m_components[i]);

		// this can throw an error
		checkShaderError(m_components[i], GL_COMPILE_STATUS, GL_FALSE, "Error: Shader Compilation Failed: ");

		glAttachShader(handle, m_components[i]);
	}
}

void ShaderSimple::compile()
{
	glBindAttribLocation(handle, VERTEX, "vertex");
	glBindAttribLocation(handle, UV, "uv");

	linkAndValidateShader(handle);

	uniforms[CAMERA_MATRIX] = glGetUniformLocation(handle, "camera_matrix");
	uniforms[OBJECTPOSITION] = glGetUniformLocation(handle, "object_pos");
}

void ShaderSimple::bind()const
{
	glUseProgram(handle);
}

ShaderSimple::~ShaderSimple()
{
	for (ushort i = 0; i < SHADERTYPE_COUNT; ++i)
	{
		glDetachShader(handle, m_components[i]);
		glDeleteShader(m_components[i]);
	}

	glDeleteProgram(handle);
}

void Shader::checkShaderError(GLuint shaderHandle, GLuint errorFlag, bool isProgram,
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