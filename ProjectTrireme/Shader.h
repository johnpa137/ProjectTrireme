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
	class ShaderProgram
	{
	public:
		ShaderProgram() {}

		// sets this as the program openGL is currently using
		void bind()const;

		// destructor
		virtual ~ShaderProgram() {}

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
		static std::string getShaderSource(const char* filename);

		// attaches a shader component
		void attachShader(const std::string& sourceStrings, const uint16_t componentHandle);

		// compile shader program
		virtual void compile() {}
	};

	
}

#endif