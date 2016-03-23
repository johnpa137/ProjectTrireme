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
		enum Attribs
		{
			VERTEX,
			ATTRIB_COUNT
		};

		Shader() {}
		// compile shader program
		virtual void compile() {}

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
		void checkShaderError(GLuint shaderHandle, GLuint errorFlag, bool isProgram,
			const std::string& errorMessage);

		// links and validates the shader while checking for errors
		// throws:
		// * glew errors when it fails to link and validate
		void linkAndValidateShader(GLuint shaderHandle);

		// get shader source code from a file to a string
		std::string getShaderSource(const char* filename);
	};

	// incomplete
	class ShaderGUI : public Shader
	{
	public:
		// attributes for the GUI shader
		enum Attribs
		{
			HEIGHTANDWIDTH = Shader::Attribs::ATTRIB_COUNT,
			//UV,
			//UVDIMENSIONS,
			ATTRIB_COUNT
		};
		
		enum Uniforms
		{
			CAMERA_MATRIX,
			UNIFORM_COUNT
		};

		enum ShaderType
		{
			VERTEX_SHADER,
			GEOMETRY_SHADER,
			FRAGMENT_SHADER,
			SHADERTYPE_COUNT
		};

		// default contructor
		ShaderGUI();

		// compile shader program
		// throws:
		// * glew errors if it fails to compile, link, or validate the program
		void compile();

		// sets this as the program openGL is currently using
		void bind()const;

		// destructor
		~ShaderGUI();

		// array of GLuint uniforms
		GLuint uniforms[UNIFORM_COUNT];
	private:
		GLuint m_components[SHADERTYPE_COUNT];
	};

	class ShaderFont : public Shader
	{
	public:
		enum Uniforms
		{
			TEXT_COLOR,
			UNIFORM_COUNT
		};

		enum ShaderType
		{
			VERTEX_SHADER,
			FRAGMENT_SHADER,
			SHADERTYPE_COUNT
		};

		ShaderFont();

		void compile();

		void bind()const;

		~ShaderFont();

		// array of GLuint uniforms
		GLuint uniforms[UNIFORM_COUNT];
	private:
		GLuint m_components[SHADERTYPE_COUNT];
	};

	// a lightless shader
	class ShaderSimple : public Shader
	{
	public:
		// attributes for the Simple shader
		enum Attribs
		{
			UV = Shader::Attribs::ATTRIB_COUNT,
			ATTRIB_COUNT
		};
	
		enum Uniforms
		{
			CAMERA_MATRIX,
			OBJECTPOSITION,
			UNIFORM_COUNT
		};
	
		enum ShaderType
		{
			VERTEX_SHADER,
			FRAGMENT_SHADER,
			SHADERTYPE_COUNT
		};
	
		// default contructor
		ShaderSimple();
	
		// compile shader program
		// throws:
		// * glew errors if it fails to compile, link, or validate the program
		void compile();
	
		// sets this as the program openGL is currently using
		void bind()const;
	
		// destructor
		~ShaderSimple();
	
		GLint handle;
		// array of GLuint uniforms
		GLuint uniforms[UNIFORM_COUNT];
	private:
		GLuint m_components[SHADERTYPE_COUNT];
	
	};
}

#endif