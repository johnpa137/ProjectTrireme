#ifndef TRIREME_FONTSHADER_H
#define TRIREME_FONTSHADER_H

#include "Shader.h"

namespace Trireme
{
	// shader specifically for fonts, do not model custom shaders after this, actually make a seperate class for custom shaders
	class FontShader : public ShaderProgram
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