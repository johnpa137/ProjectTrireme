#ifndef TRIREME_GUIRECTS_H
#define TRIREME_GUIRECTS_H

// components of UI Elements

#include "constdef.h"
#include "Texture.h"
#include "Font.h"

namespace Trireme
{
	// designates a quad on the screen to render a gui element to
	class Rect
	{
	public:
		Rect(const uint16_t x, const uint16_t y, 
			const int16_t width, const int16_t height);
		virtual ~Rect(){}
		uint16_t x, y;
		int16_t width, height; // for 90 degree rotations of texture
	};

	class Gradient
	{
	public:
		// special presets for gradients
		enum GradientProperties
		{
			HORIZONTAL_GRADIENT = 1, // binary 00000001, direction goes from left to right, will adjust radial up vector
			VERTICAL_GRADIENT = 2, // binary 00000010, direction goes from down to up, will adjust radial up vector
			CENTER_ORIGIN_GRADIENT = 4, // binary 00000100
			TOP_ORIGIN_GRADIENT = 8, // binary 00001000
			BOTTOM_ORIGIN_GRADIENT = 16, // binary 00010000
			LEFT_ORIGIN_GRADIENT = 32, // binary 00100000
			RIGHT_ORIGIN_GRADIENT = 64, // binary 01000000
		};
		// hexadecimal colors
		Gradient(const uint32_t color1, const uint32_t color2,
			const glm::vec2& origin = glm::vec2(0.0, 0.0),
			const glm::vec2& direction = glm::vec2(1.0, 0.0),
			const float offset = 0.0f);
		void applyProperty(const uint8_t properties);
		uint32_t color1, color2;
		glm::vec2 origin, direction; // origin is relative to center of gradient rect
		float offset; // when the gradient starts from the origin in the direction of the direction vector, range [0.0, 1.0]
		virtual ~Gradient(){}
		/*
		Gradient goes both directions, place origin on an edge to keep gradient from mirroring
		*/
	};

	class LinearGradient : public Gradient
	{
	public:
		// hexadecimal colors
		LinearGradient(const uint32_t color1, const uint32_t color2,
			const glm::vec2& origin = glm::vec2(0.0, 0.0),
			const glm::vec2& direction = glm::vec2(1.0, 0.0),
			const float scale = 1.0f,
			const float offset = 0.0f);
		float scale;
		~LinearGradient(){}
	};

	// simple gradient that shifts between two colors
	class RadialGradient : public Gradient
	{
	public:
		// hexadecimal colors
		RadialGradient(const uint32_t color1, const uint32_t color2,
			const glm::vec2& origin = glm::vec2(0.0, 0.0), 
			const glm::vec2& direction = glm::vec2(1.0, 0.0), 
			const glm::vec2& scale = glm::vec2(1.0, 1.0), 
			const float offset = 0.f);
		glm::vec2 scale;
		~RadialGradient(){}
	};

	struct Image
	{
		Texture* texture;
		Rect* clip; // quad coordinates in texture;
	};

	// dfawable rects are drawn on top of each other to produce a ui element
	class DrawableRect
	{
	public:
		DrawableRect(Rect* rect);
		virtual void draw()const{}
		Rect* rect;
	};

	class ColorRect : public DrawableRect
	{
	public:
		ColorRect(const uint32_t color, Rect* rect);
		uint32_t color;
		void draw()const;
		~ColorRect(){}
	};

	class LinearGradientRect : public DrawableRect
	{
	public:
		LinearGradientRect(LinearGradient* gradient, Rect* rect);
		LinearGradient* gradient;
		void draw()const;
		~LinearGradientRect(){}
	};

	class RadialGradientRect : public DrawableRect
	{
	public:
		RadialGradientRect(RadialGradient* gradient, Rect* rect);
		RadialGradient* gradient;
		void draw()const;
		~RadialGradientRect(){}
	};

	class ImageRect : public DrawableRect
	{
	public:
		ImageRect(Image* image, Rect* rect);
		Image* image;
		void draw()const;
		~ImageRect(){}
	};

	class BorderRect : public ColorRect
	{
	public:
		BorderRect(const uint32_t color, const uint16_t borderThickness, Rect* rect);
		uint16_t borderThickness;
		void draw()const;
		~BorderRect(){}
	};

	class TextRect : public DrawableRect
	{
	public:
		TextRect(Font* font, char* text, 
			const uint32_t color, const uint16_t size, 
			Rect* rect);
		Font* font;
		char* text;
		uint32_t color;
		uint16_t size;
		void draw()const;
		~TextRect(){}
	};
}

#endif