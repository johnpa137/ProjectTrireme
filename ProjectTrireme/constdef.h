// constdef.h
// this file is for defining constants used across the engine

#ifndef TRIREME_CONSTDEF_H
#define TRIREME_CONSTDEF_H

#include <cstdint>

namespace Trireme
{	
	class EngineProperties
	{
	public:
		static uint16_t *windowWidth, *windowHeight;
		static float* frameTime;
	};
}

#endif