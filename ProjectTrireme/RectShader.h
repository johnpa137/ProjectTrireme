#ifndef TRIREME_RECTSHADER_H
#define TRIREME_RECTSHADER_H

#include "Shader.h"

namespace Trireme
{
	class RectShader : public ShaderProgram
	{
	public:
		enum Attribs
		{
			VERTEX,
			ATTRIB_COUNT
		};

		virtual ~RectShader(){}

		static void fillShaderSources();

		static void clearShaderSources();

	protected:
		static std::string * shaderSources;

		enum Pipeline
		{
			VERTEX_SHADER,
			GEOMETRY_SHADER,
			FRAGMENT_SHADER,
			SHADERTYPE_COUNT
		};

		enum ShaderSources
		{
			COLOR_RECT_VS,
			IMAGE_RECT_VS,
			COLOR_RECT_GS,
			IMAGE_RECT_GS,
			GRADIENT_RECT_GS,
			BORDER_RECT_GS,
			COLOR_RECT_FS,
			IMAGE_RECT_FS,
			LINEAR_GRADIENT_RECT_FS,
			RADIAL_GRADIENT_RECT_FS,
			BORDER_RECT_FS,
			TOTAL_NUMBEROF_SHADER_SOURCES
		};

		GLuint components[SHADERTYPE_COUNT];

		virtual void compile(){}
	};

	class ColorRectShader : public RectShader
	{
	public:
		ColorRectShader();

		virtual ~ColorRectShader();

	protected:
		void compile();
	};

	class ImageRectShader : public RectShader
	{
	public:
		enum Attribs
		{
			UV = ATTRIB_COUNT,
			ATTRIB_COUNT,
		};

		ImageRectShader();

		~ImageRectShader();

	private:
		void compile();
	};

	class LinearGradientRectShader : public ColorRectShader
	{
	public:
		LinearGradientRectShader();

		~LinearGradientRectShader();

	};

	class RadialGradientRectShader : public ColorRectShader
	{
	public:
		RadialGradientRectShader();

		~RadialGradientRectShader();
	};

	class BorderRectShader : public ColorRectShader
	{
	public:
		BorderRectShader();

		~BorderRectShader();
	};
}

#endif