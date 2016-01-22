//-------------------------------------------------------------------------------------------------
#pragma once

#pragma warning (disable : 4996)

#include "SDL2\SDL.h"
#include "SDL2\SDL_image.h"
#include "GL\glew.h"
#include <vector>

namespace Trireme
{
	class Texture
	{
		// default constructor
		Texture() { handle = NULL; }

		// loads texture from filepath
		Texture(const char* filepath);
		
		// fills the pixels array and assigns the handle for the texture
		void load(const char* filepath);

		// binds this texture to used for coloring the current mesh in memory
		void bind()const;

		// unbinds this texture from memory
		void unbind()const;

		// destructor
		~Texture();

	private:
		// helper function for Texture class that obtains the pixel information in an SDL Surface,
		// at specified index in the pixel array
		Uint32 getPixel(SDL_Surface* surface, int x, int y)const;
		// array of pixel components for the texture
		// std::vector<unsigned char> pixels;
		// handle of the texture in openGL
		GLuint handle;
	};
}
	

