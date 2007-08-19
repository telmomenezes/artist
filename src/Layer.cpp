/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "Layer.h"

namespace pyc
{

Layer::Layer()
{
        mWidth = 0;
        mHeight = 0;
	mRoot = false;
	mRed = 0;
	mGreen = 0;
	mBlue = 0;
	mAlpha = 255;
}

Layer::~Layer()
{
}

void Layer::setColor(unsigned int red,
				unsigned int green,
				unsigned int blue)
{
	setColor(red, green, blue, mAlpha);
}

void Layer::setAlpha(unsigned int alpha)
{
	setColor(mRed, mGreen, mBlue, alpha);
}

void Layer::setColorRGBA(unsigned int color)
{
	unsigned int red = color & 0xFF000000;
	unsigned int green = (color & 0x00FF0000) << 8;
	unsigned int blue = (color & 0x0000FF00) << 16;
	unsigned int alpha = (color & 0x000000FF) << 24;
	
	setColor(red, green, blue, alpha);
}

void Layer::setColorRGB(unsigned int color)
{
	unsigned int red = color & 0xFF0000;
	unsigned int green = (color & 0x00FF00) << 8;
	unsigned int blue = (color & 0x0000FF) << 16;
	
	setColor(red, green, blue, mAlpha);
}

void Layer::setBackgroundColorRGB(unsigned int color)
{
	unsigned int red = color & 0xFF0000;
	unsigned int green = (color & 0x00FF00) << 8;
	unsigned int blue = (color & 0x0000FF) << 16;

	setBackgroundColor(red, green, blue);
}

void Layer::_setRoot(int width, int height)
{
	mWidth = width;
	mHeight = height;
	mRoot = true;
}

}

