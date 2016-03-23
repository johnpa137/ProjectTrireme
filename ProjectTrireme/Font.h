#ifndef TRIREME_FONT_H
#define TRIREME_FONT_H

#include "ft2build.h"
#include FT_FREETYPE_H
#include "Shader.h"
#include "GL\glew.h"

#include <string>
#include <vector>
#include <map>

namespace Trireme
{
	// wrapper class for the texture informatio of a character
	struct Character
	{
		GLuint textureID; // ID handle of the glyph texture
		glm::ivec2 size; // Size of glyph
		glm::ivec2 bearing; // Offset from baseline to left/top of glyph
		GLuint advance; // Offset to advance to next glyph
	};

	// a wrapper class for fonts
	class Font
	{
	public:
		// font constructor
		// parameters:
		// * filepath to the font file
		// * shader for the font
		Font(const char* filepath, ShaderFont* shader);

		// renders text on the screen relative to the bottom left corner of the screen x is rightwards, y is upwards
		// * text, array of characters to be rendered
		// * x, x-coordinate of bottom left corner of text rectangle
		// * y, y-coordinate of bottom left corner of text rectangle
		// * color, color of text to be rendered
		// * scale, how wide or tall the characters are relative to the default scale, 48
		void render_text(const char* text, float x, float y, const glm::vec3& color, const glm::vec2& scale = glm::vec2(1.f, 1.f))const;

		// closes Freetype library, call when done loading all fonts to deallocate freetype
		void closeLib();

		// destructor
		~Font();
	private:
		static bool libInit; // whether the freetype lib has been init
		static ushort fontCount; // how many fonts are active
		static FT_Library library; // the single freetype lib object for all fonts
		short maxYBearing; // the greatest y_offset in the font set
		// ushort windowWidth, windowHeight; // original width and height when text was first rendered
		std::map<GLchar, Character> characters;
		GLuint vao, vbo;
		ShaderFont* shaderFont;
		const char* name;
	};
}

#endif