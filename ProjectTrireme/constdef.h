// constdef.h
// this file is for defining constants used across the engine

#ifndef TRIREME_CONSTDEF_H
#define TRIREME_CONSTDEF_H

#define ERROR_MAX 256

#define DEFAULT_SCREEN_WIDTH 640

#define DEFAULT_SCREEN_HEIGHT 480

#define DEFAULT_FRAMETIME 1000.f / 60.f

#define DEFAULT_FRAMERATE 60.f

#define DEFAULT_FONT_SIZE 32

namespace Trireme
{
	typedef unsigned short ushort;
	
	class GameProperties
	{
	public:
		static ushort *windowWidth, *windowHeight;
		static float* frameTime;
	};
}

#endif