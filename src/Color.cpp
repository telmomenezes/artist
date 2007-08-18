/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "Color.h"

namespace pyc
{

Color::Color()
{
	mRed = 0.0f;
	mGreen = 0.0f;
	mBlue = 0.0f;
	mAlpha = 0.0f;
}

Color::Color(const Color &c)
{
	mRed = c.mRed;
	mGreen = c.mGreen;
	mBlue = c.mBlue;
	mAlpha = c.mAlpha;
}

Color::Color(unsigned int red, unsigned int green, unsigned int blue)
{
	mRed = ((float)red) / 255.0f;
	mGreen = ((float)green) / 255.0f;
	mBlue = ((float)blue) / 255.0f;
	mAlpha = 1.0f;
}

Color::Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
{
	mRed = ((float)red) / 255.0f;
	mGreen = ((float)green) / 255.0f;
	mBlue = ((float)blue) / 255.0f;
	mAlpha = ((float)alpha) / 255.0f;
}

Color::Color(float red, float green, float blue)
{
	mRed = red;
	mGreen = green;
	mBlue = blue;
	mAlpha = 1.0f;
}

Color::Color(float red, float green, float blue, float alpha)
{
	mRed = red;
	mGreen = green;
	mBlue = blue;
	mAlpha = alpha;
}

Color::~Color()
{
}

}

