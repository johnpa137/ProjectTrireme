#ifndef TRIREME_GUIMANAGER_H
#define TRIREME_GUIMANAGER_H

#include "Rects.h"

namespace Trireme
{
	class GUIManager
	{
	public:
		GUIManager();

		~GUIManager();
	};

	// a single texture divided into uniform clips i.e. a tileset
	class Clipset
	{
	public:
		Clipset();

		~Clipset();
	private:
		Texture* image;
		uint16_t tileWidth, tileHeight;
	};
}

#endif