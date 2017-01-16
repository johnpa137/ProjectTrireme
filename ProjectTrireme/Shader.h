#ifndef TRIREME_SHADER_H
#define TRIREME_SHADER_H

#include "constdef.h"
#include "GL\glew.h"
#define GLM_SWIZZLE
#include "glm\glm.hpp"

#include <string>
#include <fstream>

namespace Trireme
{
	// an encapsulation class for a shader program handle 
	class Shader
	{
	public:
		Shader() {}

		// sets this as the program openGL is currently using
		virtual void bind()const {}

		// destructor
		virtual ~Shader() {}

	protected:
		GLint handle;
		// for error checking during shader creation and linking process
		// shaderHandle = handle of shader component or program you're checking for errors
		// errorFlag = type of error you're checking for
		// isProgram = true, if shaderHandle is a program handle, false if component handle
		// errorMessage = errorMessage to be concatenated to openGL's error message
		// errorMessage: 'error'
		// return false if no error and true if an error occured
		// throws: 
		// * glew errors when it fails to compile
		void checkShaderError(const GLuint shaderHandle, const GLuint errorFlag, const bool isProgram,
			const std::string& errorMessage);

		// links and validates the shader while checking for errors
		// throws:
		// * glew errors when it fails to link and validate
		void linkAndValidateShader(const GLuint shaderHandle);

		// get shader source code from a file to a string
		std::string getShaderSource(const char* filename);

		// attaches a shader component
		void attachShader(const std::string& sourceStrings, const ushort componentHandle);

		// compile shader program
		virtual void compile() {}
	};

	// shader specifically for fonts, do not model custom shaders after this, actually make a seperate class for custom shaders
	class FontShader : public Shader
	{
	public:
		enum Attribs
		{
			VERTEX,
			ATTRIB_COUNT
		};

		enum Uniforms
		{
			TEXT_COLOR,
			UNIFORM_COUNT
		};

		FontShader();

		void bind()const;

		~FontShader();

		// array of GLuint uniforms
		GLuint uniforms[UNIFORM_COUNT];
	protected:
		enum Pipeline
		{
			VERTEX_SHADER,
			FRAGMENT_SHADER,
			SHADERTYPE_COUNT
		};

		GLuint components[SHADERTYPE_COUNT];

		void compile();
	};
}

#endif