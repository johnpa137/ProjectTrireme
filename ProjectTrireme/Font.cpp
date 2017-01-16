#include "Font.h"

using namespace Trireme;

using glm::vec4;

FT_Library Font::library;
bool Font::libInit = false;
ushort Font::fontCount = 0;

#define windowWidth *GameProperties::windowWidth
#define windowHeight *GameProperties::windowHeight

Font::Font(const char* filepath, FontShader* shader)
{
	if (!libInit)
		if (FT_Init_FreeType(&library))
			throw "Freetype library failed to initialize.";
		else
			libInit = true;

	FT_Face face;
	
	if (FT_New_Face(library, filepath, 0, &face))
		throw ("Font(" +  std::string(filepath) + ") failed to load.");

	if (FT_Set_Pixel_Sizes(face, 0, DEFAULT_FONT_SIZE))
		throw ("Failed to set pixel size.");

	++fontCount;
	maxYBearing = 0;

	this->shader = shader;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned char m; // this was just for testing maxYBearing

	for (unsigned char c = 0; c < UCHAR_MAX; ++c)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			continue;
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
			);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.insert(std::pair<GLchar, Character>(c, character));
		short y_bearing = face->glyph->bitmap.rows - face->glyph->bitmap_top;
		if (y_bearing > maxYBearing){
			maxYBearing = y_bearing;
			m = c;
		}
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(FontShader::Attribs::VERTEX);
	glVertexAttribPointer(FontShader::Attribs::VERTEX, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);

	name = face->family_name;
	// windowHeight = *GameProperties::windowHeight;
	// windowWidth = *GameProperties::windowWidth;

	FT_Done_Face(face);
}

void Font::render_text(const char* text, float x, float y, const glm::vec3& color, const glm::vec2& scale)const
{
	shader->bind();

	glUniform3fv(shader->uniforms[FontShader::Uniforms::TEXT_COLOR], 1, &color[0]);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);

	for (const char* i = text; *i; ++i)
	{
		Character ch = characters.at(*i);

		float x2 = (x - (windowWidth / 2.f) + ch.bearing.x) * (2.f / windowWidth);
		float y2 = (y - (windowHeight / 2.f) - ((ch.size.y - ch.bearing.y - maxYBearing) * scale.y)) * (2.f / windowHeight);

		float w = ch.size.x * (2.f / windowWidth) * scale.x;
		float h = ch.size.y * (2.f / windowHeight) * scale.y;

		float box[4][4] = {
			{ x2, y2 + h, 0.f, 0.f },
			{ x2 + w, y2 + h, 1.f, 0.f },
			{ x2, y2, 0.f, 1.f },
			{ x2 + w, y2, 1.f, 1.f },
		};

		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 16, &box[0]);
		
		// Render quad
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glBindBuffer(GL_ARRAY_BUFFER, NULL);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * scale.x; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}

	// unbinds the vao and texture
	glBindVertexArray(NULL);
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Font::closeLib()
{
	FT_Done_FreeType(library);
	libInit = false;
}

Font::~Font()
{
	for (unsigned char c = 0; c < UCHAR_MAX; ++c)
		glDeleteTextures(1, &characters[c].textureID);
	characters.clear();
	--fontCount;
	if (!fontCount && libInit){
		closeLib();
	}
}