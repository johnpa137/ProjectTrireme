#include "Rects.h"

using namespace Trireme;
using glm::vec2;

Rect::Rect(const uint16_t x, const uint16_t y,
	const int16_t width, const int16_t height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Gradient::Gradient(const uint32_t color1, const uint32_t color2,
	const vec2& origin, const vec2& direction, const float offset)
{
	this->color1 = color1;
	this->color2 = color2;
	this->origin = origin;
	this->direction = direction;
	this->offset = offset;
}

void Gradient::applyProperty(const unsigned char properties)
{
	if ((properties & (HORIZONTAL_GRADIENT | VERTICAL_GRADIENT)) ||
		(properties & (TOP_ORIGIN_GRADIENT | BOTTOM_ORIGIN_GRADIENT)) ||
		(properties & (LEFT_ORIGIN_GRADIENT | RIGHT_ORIGIN_GRADIENT)))
	{
		throw "Tried to apply conflicting gradient properties.";
	}

	if (properties & HORIZONTAL_GRADIENT){
		direction = vec2(1.0, 0.0);
	}
	if (properties & VERTICAL_GRADIENT){
		direction = vec2(0.0, 1.0);
	}
	if (properties & CENTER_ORIGIN_GRADIENT){
		origin = vec2(0.0, 0.0);
	}
	if (properties & TOP_ORIGIN_GRADIENT){
		origin.y = 1.0;
	}
	if (properties & BOTTOM_ORIGIN_GRADIENT){
		origin.y = -1.0;
	}
	if (properties & LEFT_ORIGIN_GRADIENT){
		origin.y = -1.0;
	}
	if (properties & RIGHT_ORIGIN_GRADIENT){
		origin.y = 1.0;
	}
}

LinearGradient::LinearGradient(const uint32_t color1, const uint32_t color2,
	const glm::vec2& origin, const glm::vec2& direction, const float scale,
	const float offset) : 
	Gradient(color1, color2, origin, direction, offset)
{
	this->scale = scale;
}

RadialGradient::RadialGradient(const uint32_t color1, const uint32_t color2,
	const glm::vec2& origin, const glm::vec2& direction, const glm::vec2& scale,
	const float offset) :
	Gradient(color1, color2, origin, direction, offset)
{
	this->scale = scale;
}

DrawableRect::DrawableRect(Rect* rect)
{
	this->rect = rect;
}

ColorRect::ColorRect(const uint32_t color, Rect* rect) : DrawableRect(rect)
{
	this->color = color;
}

void ColorRect::draw()const
{
	// draw commands are handled by the GUIManager
}

LinearGradientRect::LinearGradientRect(LinearGradient* gradient, Rect* rect) : DrawableRect(rect)
{
	this->gradient = gradient;
}

void LinearGradientRect::draw()const
{
	// draw commands are handled by the GUIManager
}

RadialGradientRect::RadialGradientRect(RadialGradient* gradient, Rect* rect) : DrawableRect(rect)
{
	this->gradient = gradient;
}

void RadialGradientRect::draw()const
{
	// draw commands are handled by the GUIManager
}

void ImageRect::draw()const
{
	// draw commands are handled by the GUIManager
}

ImageRect::ImageRect(Image* image, Rect* rect) : DrawableRect(rect)
{
	this->image = image;
}

BorderRect::BorderRect(const uint32_t color, const uint16_t borderThickness, Rect* rect) : ColorRect(color, rect)
{
	this->borderThickness = borderThickness;
}

void BorderRect::draw()const
{
	// draw commands are handled by the GUIManager
}

TextRect::TextRect(Font* font, char* text,
	const uint32_t color, const uint16_t size,
	Rect* rect) : DrawableRect(rect)
{
	this->font = font;
	this->text = text;
	this->color = color;
	this->size = size;
}

void TextRect::draw()const
{
	// draw commands are handled by the GUIManager
}