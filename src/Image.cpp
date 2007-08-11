/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "Image.h"

namespace pyc
{

Image::Image()
{
	mWidth = 0;
	mHeight = 0;
}

Image::~Image()
{
}

int Image::nextPowerOfTwo(int value)
{
	int result = 1;

	while (result < value)
	{
		result *= 2;
	}

	return result;
}

}

