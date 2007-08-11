/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "Canvas.h"

namespace pyc
{

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

bool Canvas::init(int width,
			int height,
			int colorDepth,
			bool fullScreen,
			bool resizable,
			bool windowDecorations)
{
	mWidth = width;
	mHeight = height;

	return true;
}

}

